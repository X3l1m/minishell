/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_words.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:02:37 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:02:37 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	space_present(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

void	cmd_split_var(t_commands *cmd, char *string)
{
	t_token		*new;
	t_token		*temp;
	char		**words;
	int			i;

	new = NULL;
	words = ft_split(string, ' ');
	if (!words)
		return ;
	cmd->com = ft_strdup(words[0]);
	if (words[1])
		new = new_token(ft_strdup(words[1]), NULL, WORD, DEFAULT);
	temp = new;
	i = 2;
	while (words[i++])
		lst_add_back_tkn(&new, new_token(ft_strdup(words[i]), 
				NULL, WORD, DEFAULT));
	lst_add_back_tkn(&new, new_token(NULL, NULL, END, DEFAULT));
	process_args(&new, cmd);
	lst_clear_tkn(&temp, &free_pointer);
	free_str_arr(words);
}

void	parse_word(t_commands **cmd, t_token **list)
{
	t_commands	*last;
	t_token		*temp;

	temp = *list;
	while (temp->type == WORD || temp->type == VAR)
	{
		last = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last->com == NULL)
		{
			if (temp->type == VAR && space_present(temp->string))
			{
				cmd_split_var(last, temp->string);
			}
			else if ((temp->string && temp->string[0])
				|| (temp->next->type != WORD && temp->next->type != VAR))
			{
				last->com = ft_strdup(temp->string);
			}
			temp = temp->next;
		}
		else
			process_args(&temp, last);
	}
	*list = temp;
}
