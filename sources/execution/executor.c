#include <minishell.h>

int	find_char(char *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

void	setio(t_commands *cmd)
{
	if (cmd->fd_data->fd_in != -1)
	{
		if (dup2(cmd->fd_data->fd_in, STDIN_FILENO) == -1)
			perror("dup2 (executor: 21)");
		close(cmd->fd_data->fd_in);
	}
	if (cmd->fd_data->fd_out != -1)
	{
		if (dup2(cmd->fd_data->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 (executor: 27)");
		close(cmd->fd_data->fd_out);
	}
}

void	exec_check(char *com, char *path)
{
	struct stat	info;

	if (stat(path, &info) == -1)
		exit(cmd_err_msg(com, NULL, "No such file or directory", 127));
	else if (S_ISDIR(info.st_mode))
		exit(cmd_err_msg(com, NULL, "is a directory", 126));
	else if ((info.st_mode & S_IXUSR) == 0)
		exit(cmd_err_msg(com, NULL, "Permission denied", 126));
}

int	run_com(t_commands *cmd, t_dllist *env)
{
	char	*path;

	if (!cmd->com || !*cmd->com)
		exit (0);
	if (!find_char(cmd->com, '/'))
		path = pathf(cmd->com, env);
	else
		path = cmd->com;
	if (!path)
		exit (err_msg(cmd->com, "command not found", 127));
	exec_check(cmd->com, path);
	execve(path, cmd->args, env->list);
	perror(cmd->com);
	exit(errno);
}

int	env_com(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_putendl_fd(env[i++], STDOUT_FILENO);
	return (SUCCES);
}

int	builtin_com(t_data *data)
{
	if (!ft_strcmp(data->cmd->com, "echo"))
		return (echo_com(data->cmd));
	if (!ft_strcmp(data->cmd->com, "cd"))
		return (cd_com(data->cmd));
	if (!ft_strcmp(data->cmd->com, "pwd"))
		return (pwd_com());
	if (!ft_strcmp(data->cmd->com, "export"))
		return (export_com(data->cmd, data->env));
	if (!ft_strcmp(data->cmd->com, "unset"))
		return (unset_com(data->cmd, data->env));
	if (!ft_strcmp(data->cmd->com, "env"))
		return (env_com(data->env->list));
	// if (!ft_strcmp(cmd->com, "exit"))
		
	return (-1);
}

void	child(t_data *data, int old_in, pid_t *pip)
{
	int	b;

	close(pip[0]);
	if (old_in != -1)
	{
		dup2(old_in, STDIN_FILENO);
		close(old_in);
	}
	if (data->cmd->next)
		dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	if (data->cmd->fd_check == 1)
		setio(data->cmd);
	else if (data->cmd->fd_check == -1)
		exit (1);
	b = builtin_com(data);
	if (b != -1)
		exit(b);
	run_com(data->cmd, data->env);
}

int	get_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (SUCCES);
}

int	fork_run(t_commands *cmd, t_dllist *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FAILURE);
	if (!pid)
		run_com(cmd, env);
	return (get_exit_status(pid));
}

int	single_exec(t_data *data)
{
	int	b;
	int	o_stdin;
	int	o_stdout;

	if (data->cmd->fd_check == 1)
	{
		o_stdin = dup(STDIN_FILENO);
		o_stdout = dup(STDOUT_FILENO);
		setio(data->cmd);
	}
	else if (data->cmd->fd_check == -1)
		return (1);
	b = builtin_com(data);
	if (b == -1)
		b = fork_run(data->cmd, data->env);
	if (data->cmd->fd_check)
	{
		dup2(o_stdout, STDOUT_FILENO);
		dup2(o_stdin, STDIN_FILENO);
		close(o_stdin);
		close(o_stdout);
	}
	return (b);
}

int	executor(t_data *data)
{
	pid_t	pid;
	int		pip[2];
	int		old_in;

	old_in = -1;
	if (!data->cmd->pipe)
		return (single_exec(data));
	while (data->cmd)
	{
		if (pipe(pip) == -1)
			return (FAILURE);
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		if (!pid)
			child(data, old_in, pip);
		if (old_in != -1)
			close(old_in);
		old_in = pip[0];
		close(pip[1]);
		data->cmd = data->cmd->next;
	}
	close(old_in);
	return (get_exit_status(pid));
}
