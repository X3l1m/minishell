/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:02:43 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:02:44 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	fill_heredoc(t_data *data, t_data_fd *io, int fd)
{
	char	*input;
	bool	success;
	int		gback;

	gback = g_exit;
	success = false;
	input = NULL;
	while (true)
	{
		set_signals_interactive(1);
		input = readline(">");
		set_signals_noninteractive();
		if (gback != g_exit || !check_line_hd(data, io, &input, &success))
		{
			g_exit = gback;
			break ;
		}
		ft_putendl_fd(input, fd);
		free_pointer(input);
	}
	free_pointer(input);
	return (success);
}

bool	build_heredoc(t_data *data, t_data_fd *io)
{
	pid_t	pid;
	bool	ret;
	int		temp_fd;

	pid = fork();
	if (pid == -1)
		return (false);
	if (!pid)
	{
		temp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ret = fill_heredoc(data, io, temp_fd);
		close(temp_fd);
		if (!ret)
			exit(-1);
		exit(0);
	}
	g_exit = get_exit_status(pid);
	if (g_exit)
	{
		if (g_exit == -1)
			g_exit = 0;
		return (false);
	}
	return (true);
}

bool	check_exit(t_commands **cmd)
{
	if (g_exit == 130)
	{
		lst_clear_cmd(cmd, &free_pointer);
		return (false);
	}
	return (true);
}

bool	parse_heredoc(t_data *data, t_commands **last_cmd, t_token **list)
{
	t_token		*temp;
	t_commands	*cmd;
	t_data_fd	*io;

	temp = *list;
	cmd = lst_last_cmd(*last_cmd);
	init_data_fd(cmd);
	io = cmd->fd_data;
	if (!remove_old_ref(io, true))
		return (true);
	io->infile = get_heredoc_name();
	io->delim_hd = get_delim_hd(temp->next->string, io->quotes_hd);
	if (build_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*list = temp;
	unlink(io->infile);
	return (check_exit(last_cmd));
}
