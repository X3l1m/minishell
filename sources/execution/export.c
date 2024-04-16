/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:31 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/06 14:28:46 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*connect_with(char *s1, char c, char *s2)
{
	int		len1;
	int		len2;
	char	*new;

	len1 = ft_strlen(s1) + 1;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	new = ft_calloc(sizeof(char), len1 + len2 + 1);
	if (!new)
		return (NULL);
	cpy_last(new, s1, 0);
	new[len1 - 1] = c;
	cpy_last(new, s2, len1);
	new[len1 + len2] = 0;
	return (new);
}

int	init_char_env(t_dllist *env, t_dlnode *tmp)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (i < env->listlen)
	{
		if (tmp->value)
		{
			env->list[e] = connect_with(tmp->name, '=', tmp->value);
			if (!env->list[e++])
				return (error_mini("Malloc(export: 70)", 1));
		}
		tmp = tmp->next;
		i++;
	}
	env->list[e] = NULL;
	return (SUCCES);
}

int	update_evn(t_dllist *env)
{
	int			i;
	int			env_len;

	i = env->listlen;
	env_len = 0;
	if (env->list)
		free_dub(env->list);
	while (i--)
	{
		if (env->head->value)
			env_len++;
		env->head = env->head->next;
	}
	env->list = malloc(sizeof(char *) * (env_len + 1));
	if (!env->list)
		return (error_mini("Malloc(export: 61)", 1));
	return (init_char_env(env, env->head));
}

void	export_print(t_dllist *env)
{
	int			i;

	i = env->listlen;
	while (i--)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->head->name, STDOUT_FILENO);
		if (env->head->value)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
			ft_putstr_fd(env->head->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		write(1, "\n", 1);
		env->head = env->head->next;
	}
}

t_dlnode	*find_env(t_dllist *env, char *name)
{
	int			i;
	t_dlnode	*tmp;

	tmp = env->head;
	i = env->listlen;
	while (i--)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
