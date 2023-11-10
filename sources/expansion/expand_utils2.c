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
	if (!tmp)
		return (NULL);
	return (ft_strdup(tmp->value));
}

bool	valid_var(t_data *data, char *var)
{
	char	*temp;

	temp = get_evn_char(data->env, var);
	if (temp == NULL)
		return (false);
	return (true);
}
