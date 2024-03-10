/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:29 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:30 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*add_path(char *path, char *com, char c)
{
	int		len;
	int		len2;
	int		add;
	char	*new;

	if (!path)
		return (NULL);
	add = 0;
	len = ft_strlen(path);
	len2 = ft_strlen(com);
	if (path[len - 1] != c)
		add = 1;
	new = malloc(len + len2 + add + 1);
	if (!new)
		error_mini("Malloc(find_path: 19)", -1);
	if (add)
		new[len] = c;
	ft_memcpy(new, path, len);
	ft_memcpy(new + len + add, com, len2);
	new[len + len2 + add] = 0;
	return (new);
}

char	*pathf(char *com, t_dllist *env)
{
	int			i;
	char		**path;
	char		*cp;
	t_dlnode	*tmp;

	i = 0;
	cp = com;
	tmp = find_env(env, "PATH");
	if (!tmp)
		return (com);
	path = ft_split(tmp->value, ':');
	if (!path)
		error_mini("ft_split(find_path: 39)", -1);
	while (cp)
	{
		cp = add_path(path[i++], com, '/');
		if (!cp)
			break ;
		if (!access(cp, X_OK))
			break ;
		free(cp);
	}
	free_str_arr(path);
	return (cp);
}
