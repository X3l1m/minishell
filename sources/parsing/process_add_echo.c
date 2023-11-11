#include <minishell.h>

char	**merge_into_array(int i, char **words, t_commands *cmd, t_token *temp)
{
	int	j;

	j = 0;
	while (j < i)
	{
		words[j] = ft_strdup(cmd->args[j]);
		j++;
	}
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->join == true)
			words[j] = merge_vars(&temp);
		else
			words[j] = ft_strdup(temp->string);
		j++;
		temp = temp->next;
	}
	words[j] = NULL;
	return (words);
}

int	add_args_ecmd(t_token **list, t_commands *cmd)
{
	t_token	*temp;
	int		count;
	int		i;
	char	**words;

	i = 0;
	remove_empty_vars(list);
	temp = *list;
	count = count_e_args(temp);
	while (cmd->args[i])
		i++;
	words = malloc(sizeof(char *) * (count + i + 1));
	if (!words)
		return (1);
	words = merge_into_array(i, words, cmd, temp);
	free_str_arr(cmd->args);
	cmd->args = words;
	while (temp->type == WORD || temp->type == VAR)
		temp = temp->next;
	(*list) = temp;
	return (0);
}
