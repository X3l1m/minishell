#include <minishell.h>

void	handle_pipe(t_commands **cmds, t_token **list)
{
	t_commands	*last;

	last = lst_last_cmd(*cmds);
	last->pipe = true;
	lst_add_back_cmd(&last, lst_new_command(false));
	*list = (*list)->next;
}

static int	check_commands_empty(t_data *data)
{
	t_commands	*cmd;

	if (!data || !data->cmd)
	{
		if (!data)
			printf("no data\n");
		else if (!data->cmd)
			printf("no cmd\n");
		return (SUCCES);
	}
	cmd = data->cmd;
	while (cmd && cmd->com)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->com);
			if (!cmd->args[0])
				return (error_mini("ft_split(parse_data: 46)", 1));
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	return (SUCCES);
}

void	parse_data(t_data *data, t_token *token)
{
	t_token	*temp;

	if (token->type == END)
		return ;
	temp = token;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_add_back_cmd(&data->cmd, lst_new_command(false));
		if (temp->type == HEREDOC)
			parse_heredoc(data, &data->cmd, &temp);
		else if (temp->type == WORD || temp->type == VAR)
			parse_word(&data->cmd, &temp);
		else if (temp->type == INPUT)
			parse_input(&data->cmd, &temp);
		else if (temp->type == TRUNC)
			parse_trunc(&data->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp);
		else if (temp->type == PIPE)
			handle_pipe(&data->cmd, &temp);
		else if (temp->type == END)
			break ;
	}
	check_commands_empty(data);
	return ;
}
