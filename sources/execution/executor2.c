/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 12:53:44 by seyildir      #+#    #+#                 */
/*   Updated: 2024/04/16 12:53:44 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
