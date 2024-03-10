/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:42 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:43 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**split_one(char *str, char c)
{
	int		i;
	int		len;
	int		len2;
	char	**new;

	i = 0;
	len = ft_strlen(str);
	new = ft_calloc(sizeof(char *), 3);
	if (!new)
		error_mini(("Mallloc (envp: 29)"), -1);
	while (str[i] != c)
		i++;
	len2 = len - i - 1;
	new[0] = ft_calloc(sizeof(char), i + 1);
	if (!new[0])
		error_mini(("Mallloc (envp: 35)"), -1);
	new[1] = ft_calloc(sizeof(char), len2 + 1);
	if (!new[1])
		error_mini(("Mallloc (envp: 38)"), -1);
	while (i--)
		new[0][i] = str[i];
	while (len2--)
		new[1][len2] = str[--len];
	return (new);
}

t_dllist	*envcpy(char **envp)
{
	t_dllist	*env;
	t_dlnode	*new;
	int			i;
	char		**tmp;

	i = 0;
	env = cdl_listinit();
	if (env == NULL)
		exit (23);
	while (envp[i])
	{
		tmp = split_one(envp[i], '=');
		if (tmp == NULL)
			error_mini("Malloc (envp: 62)", -1);
		new = cdl_nodenew(tmp[0], tmp[1]);
		if (!new)
			error_mini("Malloc (envp: 65)", -1);
		cdl_listaddback(env, new);
		free (tmp);
		i++;
	}
	return (env);
}
