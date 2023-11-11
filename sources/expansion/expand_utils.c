#include <minishell.h>

int	var_length(char *string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string[i] != '$')
		i++;
	if (!string[i])
		return (0);
	i++;
	if ((string[i] >= '0' && string[i] <= '9') || string[i] == '?')
		return (count + 1);
	while (string[i])
	{
		if (!ft_isalnum(string[i]) && string[i] != '_')
			break ;
		i++;
		count++;
	}
	return (count);
}

void	string_init(char *new, char *string, int index, int i)
{
	int	s;
	int	len;

	s = 0;
	len = 0;
	while (string[s])
	{
		if (s == index)
			s += i;
		if (!string[s])
			break;
		new[len] = string[s];
		s++;
		len++;
	}
}

static bool	erase_var(t_token *list, char *string, int index)
{
	int		i;
	int		len;
	char	*new;

	i = var_length(string + index) + 1;
	len = ft_strlen(string) - i;
	new = malloc(len + 1);
	if (!new)
		return (false);
	new[len] = 0;
	if (len)
		string_init(new, string, index, i);
	free(list->string);
	list->string = new;
	return (true);
}

static bool	erase_replace_var(t_token *list, char *string,
				char *var, int index)
{
	int		len;
	char	*new;

	len = (ft_strlen(string) - var_length(string + index) + ft_strlen(var));
	new = get_new_string(string, var, len, index);
	if (!new)
		return (false);
	if (list )
	{
		free_pointer(list->string);
		list->string = new;
	}
	return (true);
}

int	replace_var(t_token *list, char *var, int index)
{
	if (var == NULL)
	{
		if(!erase_var(list, list->string, index))
			return (error_mini("Malloc(expand_utils: 78)", 1));
	}
	else
	{
		if(!erase_replace_var(list, list->string, var, index))
			return (error_mini("Malloc(expand_utils: 83)", 1));
	}
	free_pointer(var);
	return (SUCCES);
}
