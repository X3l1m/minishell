#include <minishell.h>

static int	handle_append(t_data_fd *io, char *filename, char *o_filename)
{
	if (!remove_old_ref(io, false))
		return (-1);
	io->outfile = ft_strdup(filename);
	if (io->outfile && io->outfile[0] == '\0')
		return (cmd_err_msg(o_filename, NULL, ERR_AR, -1));
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		return (cmd_err_msg(io->outfile, NULL, strerror(errno), -1));
	return (1);
}

void	parse_append(t_commands **cmd, t_token **list)
{
	t_commands	*last;
	t_token		*temp;

	last = lst_last_cmd(*cmd);
	temp = *list;
	init_data_fd(last);
	last->fd_check = handle_append(last->fd_data, temp->next->string, temp->next->string_cpy);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*list = temp;
}
