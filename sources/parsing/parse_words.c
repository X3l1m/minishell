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
				last->com = ft_strdup(temp->string);
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
