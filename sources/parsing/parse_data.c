/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 12:47:06 by linux         #+#    #+#                 */
/*   Updated: 2024/03/09 00:29:42 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_pipe(t_commands **cmds, t_token **list)
{
	t_commands	*last;

	last = lst_last_cmd(*cmds);
	last->pipe = true;
	lst_add_back_cmd(&last, lst_new_command(false));
	*list = (*list)->next;
}

int	check_commands_empty(t_data *data)
{
	t_commands	*cmd;

	cmd = data->cmd;
	while (cmd && cmd->com)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			if (!cmd->args)
				return (error_mini("Malloc(parse_data: 35)", 1));
			cmd->args[0] = ft_strdup(cmd->com);
			if (!cmd->args[0])
				return (error_mini("Malloc(parse_data: 39)", 1));
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	return (SUCCES);
}

bool	parse_loop(t_token **temp, t_token **token, t_data **data, bool *ret)
{
	if (*temp == *token)
		lst_add_back_cmd(&(*data)->cmd, lst_new_command(false));
	if ((*temp)->type == HEREDOC)
		*ret = parse_heredoc(*data, &(*data)->cmd, &(*temp));
	else if ((*temp)->type == WORD || (*temp)->type == VAR)
		parse_word(&(*data)->cmd, &(*temp));
	else if ((*temp)->type == INPUT)
		parse_input(&(*data)->cmd, &(*temp));
	else if ((*temp)->type == TRUNC)
		parse_trunc(&(*data)->cmd, &(*temp));
	else if ((*temp)->type == APPEND)
		parse_append(&(*data)->cmd, &(*temp));
	else if ((*temp)->type == PIPE)
		handle_pipe(&(*data)->cmd, &(*temp));
	else if ((*temp)->type == END)
		return (false);
	return (true);
}

void	parse_data(t_data *data, t_token *token)
{
	t_token	*temp;
	bool	ret;

	ret = true;
	temp = token;
	while (temp->next != NULL)
	{
		if (!parse_loop(&temp, &token, &data, &ret))
			break ;
		if (!ret)
			return ;
	}
	check_commands_empty(data);
}
