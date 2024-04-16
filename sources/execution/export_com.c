/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_com.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:32 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:32 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cpy_last(char *s1, char *s2, int start)
{
	int	i;

	i = 0;
	while (s2[i])
		s1[start++] = s2[i++];
}

int	check_valid(char *str)
{
	int	v;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	v = 0;
	while (str[++v])
	{
		if (str[v] == '=')
			return (v);
		if (!ft_isalnum(str[v]) && str[v] != '_')
			return (-1);
	}
	return (0);
}

int	cpy_var(t_dllist *env, char *name, char *value)
{
	t_dlnode	*node;

	node = find_env(env, name);
	if (!node)
	{
		node = cdl_nodenew(name, value);
		if (!node)
			return (error_mini("Malloc(export: 24)", 1));
		cdl_listaddback(env, node);
	}
	else if (value)
	{
		free_pointer(node->value);
		node->value = value;
		free(name);
	}
	return (SUCCES);
}

int	export_var(t_dllist *env, char *arg, int v)
{
	char		*name;
	char		*value;

	if (v)
	{
		name = ft_substr(arg, 0, v);
		value = ft_strdup(arg + (v + 1));
		if (!value)
			return (error_mini("Malloc(export: 24)", 1));
	}
	else
	{
		name = ft_strdup(arg);
		if (!name)
			return (error_mini("Malloc(export: 24)", 1));
		value = NULL;
	}
	if (!name)
		return (error_mini("Malloc(export: 24)", 1));
	if (cpy_var(env, name, value))
		return (FAILURE);
	return (update_evn(env));
}

int	export_com(t_commands *cmd, t_dllist *env)
{
	int	i;
	int	v;

	i = 0;
	while (cmd->args[++i])
	{
		v = check_valid(cmd->args[i]);
		if (v != -1)
		{
			if (export_var(env, cmd->args[i], v))
				return (FAILURE);
		}
		else
			g_exit = cmd_err_msg("export",
					cmd->args[i], "not a valid identifier", 1);
	}
	if (!cmd->args[1])
		export_print(env);
	return (g_exit);
}
