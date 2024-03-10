/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_var.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:15 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:15 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_status(t_token **node, char c)
{
	if (c == '\'' && (*node)->status == DEFAULT)
		(*node)->status = S_QUOTES;
	else if (c == '\"' && (*node)->status == DEFAULT)
		(*node)->status = D_QUOTES;
	else if (c == '\'' && (*node)->status == S_QUOTES)
		(*node)->status = DEFAULT;
	else if (c == '\"' && (*node)->status == D_QUOTES)
		(*node)->status = DEFAULT;
}

/*sleepcoded, check later*/
bool	next_char_sep(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (true);
	return (false);
}

/*sleepcoded, check later*/
bool	var_between_quotes(char *string, int i)
{
	if (i > 0)
	{
		if (string[i - 1] == '\"' && string[i + 1] == '\"')
			return (true);
		return (false);
	}
	return (false);
}

char	*get_val(t_data *data, t_token *temp, char *string)
{
	char	*var;
	char	*value;

	var = id_variable(string);
	if (var && valid_var(data, var) == true)
	{
		if (temp)
			temp->valid_var = true;
		value = get_evn_char(data->env, var);
	}
	else if (var && var[0] == '?')
		value = ft_itoa(g_exit);
	else
		value = NULL;
	free_pointer(var);
	return (value);
}

/*sleepcoded, check later*/
int	expand_var(t_data *data, t_token **list)
{
	t_token		*temp;
	int			i;

	temp = *list;
	while (temp)
	{
		i = 0;
		while (temp->string[i] && temp->type == VAR)
		{
			update_status(&temp, temp->string[i]);
			if (temp->string[i] == '$' && next_char_sep(temp->string[i + 1])
				&& !var_between_quotes(temp->string, i)
				&& (temp->status == DEFAULT || temp->status == D_QUOTES))
			{
				if (replace_var(temp, get_val(data, temp, temp->string + i), i))
					return (FAILURE);
			}
			else if (temp->string[i])
				i++;
		}
		temp = temp->next;
	}
	handle_quotes(data);
	return (SUCCES);
}
