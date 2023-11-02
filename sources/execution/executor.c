#include <minishell.h>

int	check_exec(char *com)
{

}

int	find_char(char *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

int	run_com(t_commands *cmd, t_dllist *env)
{
	char	*path;

	if (cmd->fd_check)
	{
		dup2(cmd->fd_data->fd_in, STDIN_FILENO);
		dup2(cmd->fd_data->fd_out, STDOUT_FILENO);
		close(cmd->fd_data->fd_in);
		close(cmd->fd_data->fd_out);
	}
	if (!find_char(cmd->com, '/'))
		path = pathf(cmd->com, env->head);
	else
		path = cmd->com;
	if (!path)
	{
		err_msg(cmd->com, "command not found");
		exit(127);
	}
	execve(path, cmd->args, env->list);
	perror(cmd->com);
}

int	builtin_com(t_commands *cmd, t_dllist *env)
{
	if (!ft_strcmp(cmd->com, "echo"))
		echo_com(cmd);
	if (!ft_strcmp(cmd->com, "cd"))
		return (cd_com(cmd));
	if (!ft_strcmp(cmd->com, "pwd"))
		return (pwd_com());
	// if (!ft_strcmp(cmd->com, "export"))
	// if (!ft_strcmp(cmd->com, "unset"))
	// if (!ft_strcmp(cmd->com, "env"))
	// if (!ft_strcmp(cmd->com, "exit"))
	return (-1);
}

int	executor(t_commands *cmd, t_dllist *env)
{
	pid_t	pid;
	int		pip[2];
	int		old_in;

	if(builtin_com(cmd, env) != -1)
		cmd = cmd->next;
	return (0);
/* 	if (!cmd->pipe)
		return (single_com(cmd, env)); */
	old_in = -1;
	while (cmd)
	{

		if (pipe(pip) == -1)
			return (FAILURE);
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		if (!pid)//child
		{
			close(pip[0]);
			if(old_in != -1)
			{
				dup2(old_in, STDIN_FILENO);
				close(old_in);
			}
			if (cmd->next)
				dup2(pip[1], STDOUT_FILENO);
			close(pip[1]);
			fprintf(stderr, "\033[0;32m\n");
			run_com(cmd, env);
			exit(1);
		}
		else
		{
				close(old_in);
				old_in = pip[0];
				close(pip[1]);
		}
		cmd = cmd->next;
	}
	close(old_in);
	while (wait(NULL) != -1);
	waitpid(pid, NULL, 0);
	return (SUCCES);
}
