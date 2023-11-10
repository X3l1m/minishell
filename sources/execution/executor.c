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

int	run_com(t_commands *cmd, t_dllist *env)
{
	char	*path;

	if (!find_char(cmd->com, '/'))
		path = pathf(cmd->com, env);
	else
		path = cmd->com;
	if (!path)
	{
		err_msg(cmd->com, "command not found");
		exit(127);
	}
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
	if (cmd->fd_check)
		setio(cmd);
	b = builtin_com(cmd, env);
	if (b != -1)
		exit(b);
	run_com(cmd, env);
}

int	get_exit_status(void)
{
	int	status;

	while (wait(&status) != -1)
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
	return (get_exit_status());
}

int	single_exec(t_commands *cmd, t_dllist *env)
{
	int	b;
	int	o_stdin;
	int	o_stdout;

	if (cmd->fd_check)
	{
		o_stdin = dup(STDIN_FILENO);
		o_stdout = dup(STDOUT_FILENO);
		setio(cmd);
	}
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
		close(old_in);
		old_in = pip[0];
		close(pip[1]);
		cmd = cmd->next;
	}
	close(old_in);
	return (get_exit_status());
}
