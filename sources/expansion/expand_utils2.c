/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:16 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:16 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*id_variable(char *string)
{
	char	*var;
	int		start;
	int		size;
	int		i;

	i = 0;
	start = 0;
	while (string[i])
	{
		if (string[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	size = var_length(string);
	var = ft_substr(string, start, size);
	if (!var)
		return (NULL);
	return (var);
}

char	*get_evn_char(t_dllist *env, char *var)
{
	t_dlnode	*tmp;

	tmp = find_env(env, var);
	if (!tmp || !tmp->value)
		return (NULL);
	return (ft_strdup(tmp->value));
}

bool	valid_var(t_data *data, char *var)
{
	t_dlnode	*temp;

	temp = find_env(data->env, var);
	if (!temp || !temp->value)
		return (false);
	return (true);
}
