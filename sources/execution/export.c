#include <minishell.h>

void	free_dub(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	cpy_last(char *s1, char *s2, int start)
{
	int	i;

	i = 0;
	while (s2[i])
		s1[start++] = s2[i++];
}

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
	env->list = malloc(sizeof(char*) * (env_len + 1));
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
	return(NULL);
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
	return(0);
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
			g_exit = cmd_err_msg("export", cmd->args[i], "not a valid identifier", 1);
	}
	if (!cmd->args[1])
		export_print(env);
	return (g_exit);
}
