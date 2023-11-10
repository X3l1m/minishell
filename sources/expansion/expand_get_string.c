#include <minishell.h>

void	copy_new_var(char *new, char *var, int *j)
{
	int	copy;

	copy = 0;
	while (var[copy])
	{
		new[*j] = var[copy];
		(*j)++;
		copy++;
	}
}

char	*get_new_string(char *old, char *var, int len, int index)
{
	char	*new_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_string = (char *)malloc(sizeof(char) * len);
	if (!new_string)
		return (NULL);
	while (old[i])
	{
		if (old[i] == '$' && i == index)
		{
			copy_new_var(new_string, var, &j);
			i = i + var_length(old + index) + 1;
			if (old[i] == '\0')
				break ;
		}
		new_string[j++] = old[i++];
	}
	new_string[j] = '\0';
	return (new_string);
}
