#include <minishell.h>

int	count_args(t_token *list)
{
	int	i;

	i = 0;
	while (list && (list->type == WORD || list->type == VAR))
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**merge_strings(char **words, t_commands *cmd, t_token **list, int size)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *list;
	while (i < size)
	{
		words[i] = cmd->args[i];
		i++;
	}
	while (temp->type == WORD || temp->type == VAR)
	{
		words[i] = ft_strdup(temp->string);
		i++;
		temp = temp->next;
	}
	words[i] = NULL;
	return (words);
}

bool	add_args_cmd(t_token **list, t_commands *cmd)
{
	int		i;
	int		size;
	char	**words;
	t_token	*temp;

	i = 0;
	size = 0;
	temp = *list;
	while (temp->type == WORD || temp->type == VAR)
	{
		i++;
		temp = temp->next;
	}
	while (cmd->args[size])
		size++;
	words = (char **)malloc(sizeof(char *) * (i + size + 1));
	if (!words)
		return (error_mini("Malloc (protcess_args: 59)", 1));
	words = merge_strings(words, cmd, list, size);
	free(cmd->args);
	cmd->args = words;
	free_str_arr(words);
	return (0);
}

bool	create_args_cmd(t_token **list, t_commands *cmd)
{
	int		i;
	int		size;
	t_token	*temp;

	i = 0;
	temp = *list;
	size = count_args(*list);
	cmd->args = (char **)malloc(sizeof(char *) * (size + 2));
	if (!cmd->args)
		return (error_mini("Malloc (protcess_args: 79)", 1));
	temp = *list;
	cmd->args[i] = ft_strdup(cmd->com);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		cmd->args[i] = ft_strdup(temp->string);
		i++;
		temp = temp->next;
	}
	cmd->args[i] = NULL;
	*list = temp;
	return (0);
}

bool	process_args(t_token **list, t_commands *cmd)
{
	if (!ft_strcmp(cmd->com, "echo"))
	{
		if (!cmd->args)
			return (create_args_ecmd(list, cmd));
		else
			return (add_args_ecmd(list, cmd));
	}
	else
	{
		if (cmd && !(cmd->args))
			return (create_args_cmd(list, cmd));
		else
			return (add_args_cmd(list, cmd));
	}
	return (true);
}
