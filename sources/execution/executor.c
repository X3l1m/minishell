/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:38 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:39 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	if (!ft_strcmp(data->cmd->com, "exit"))
		return (exit_com(data));
	return (-1);
}
