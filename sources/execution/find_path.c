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
	if (add)
		new[len] = c;
	ft_memcpy(new, path, len);
	ft_memcpy(new + len + add, com, len2);
	new[len + len2 + add] = 0;
	return (new);
}

char	*find_env(t_dlnode *env, char *name)
{
	while (ft_strcmp(env->name, name))
		env = env->next;
	return (env->value);
}

char	*pathf(char *com, t_dlnode *env)
{
	int		i;
	char	**path;
	char	*cp;

	i = 0;
	cp = com;
	path = ft_split(find_env(env, "PATH"), ':');
	while (cp)
	{
		cp = add_path(path[i++], com, '/');
		if (!access(cp, X_OK))
			return (cp);
		free(cp);
	}
	return (NULL);
}
