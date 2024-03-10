/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:11 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:11 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*figure this out, something aint right*/
int	count_length(char *string, int count, int i)
{
	int	status;

	status = DEFAULT;
	while (string[i])
	{
		if ((string[i] == '\'' || string[i] == '\"') && status == DEFAULT)
		{
			if (string[i] == '\'')
				status = S_QUOTES;
			else if (string[i] == '\"')
				status = D_QUOTES;
			i++;
			continue ;
		}
		else if ((string[i] == '\'' && status == S_QUOTES)
			|| (string[i] == '\"' && status == D_QUOTES))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count);
}

bool	remove_quotes(t_token **list)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(count_length((*list)->string, 0, 0) + 1);
	if (!new)
		return (false);
	while ((*list)->string[i])
	{
		if (((*list)->string[i] == '\''
				|| (*list)->string[i] == '\"') && (*list)->status == DEFAULT)
		{
			change_status_quote(list, &i);
			continue ;
		}
		else if (change_status_default(list, &i) == true)
			continue ;
		new[j++] = (*list)->string[i++];
	}
	new[j] = '\0';
	sort_strings(list, new);
	return (true);
}

bool	quotes_found(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	handle_quotes(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (quotes_found(temp->string) == true)
			remove_quotes(&temp);
		temp = temp->next;
	}
}
