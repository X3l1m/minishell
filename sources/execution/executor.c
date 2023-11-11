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

int	builtin_com(t_commands *cmd, t_dllist *env)
{
	if (!ft_strcmp(cmd->com, "echo"))
		return (echo_com(cmd));
	if (!ft_strcmp(cmd->com, "cd"))
		return (cd_com(cmd));
	if (!ft_strcmp(cmd->com, "pwd"))
		return (pwd_com());
	if (!ft_strcmp(cmd->com, "export"))
		return (export_com(cmd, env));
	if (!ft_strcmp(cmd->com, "unset"))
		return (unset_com(cmd, env));
	if (!ft_strcmp(cmd->com, "env"))
		return (env_com(env->list));
	// if (!ft_strcmp(cmd->com, "exit"))
	return (-1);
}

void	child(t_commands *cmd, t_dllist *env, int old_in, pid_t *pip)
{
	int	b;

	close(pip[0]);
	if (old_in != -1)
	{
		dup2(old_in, STDIN_FILENO);
		close(old_in);
	}
	if (cmd->next)
		dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	if (cmd->fd_check == 1)
		setio(cmd);
	else if (cmd->fd_check == -1)
		exit (1);
	b = builtin_com(cmd, env);
	if (b != -1)
		exit(b);
	run_com(cmd, env);
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

int	single_exec(t_commands *cmd, t_dllist *env)
{
	int	b;
	int	o_stdin;
	int	o_stdout;

	if (cmd->fd_check == 1)
	{
		o_stdin = dup(STDIN_FILENO);
		o_stdout = dup(STDOUT_FILENO);
		setio(cmd);
	}
	else if (cmd->fd_check == -1)
		return (1);
	b = builtin_com(cmd, env);
	if (b == -1)
		b = fork_run(cmd, env);
	if (cmd->fd_check)
	{
		dup2(o_stdout, STDOUT_FILENO);
		dup2(o_stdin, STDIN_FILENO);
		close(o_stdin);
		close(o_stdout);
	}
	return (b);
}

int	executor(t_commands *cmd, t_dllist *env)
{
	pid_t	pid;
	int		pip[2];
	int		old_in;

	old_in = -1;
	if (!cmd->pipe)
		return (single_exec(cmd, env));
	while (cmd)
	{
		if (pipe(pip) == -1)
			return (FAILURE);
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		if (!pid)
			child(cmd, env, old_in, pip);
		if (old_in != -1)
			close(old_in);
		old_in = pip[0];
		close(pip[1]);
		cmd = cmd->next;
	}
	close(old_in);
	return (get_exit_status(pid));
}
