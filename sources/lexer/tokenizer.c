#include <minishell.h>

int	set_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = S_QUOTES;
	else if (str[i] == '\"' && status == DEFAULT)
		status = D_QUOTES;
	else if (str[i] == '\'' && status == S_QUOTES)
		status = DEFAULT;
	else if (str[i] == '\"' && status == D_QUOTES)
		status = DEFAULT;
	return (status);
}

int	tokenizer(t_data *data, char *str)
{
	int		i;
	int		start;
	int		end;
	int		status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = save_part(data, &i, str, start);
	}
	if (status != DEFAULT)
	{
		if (status == D_QUOTES)
			ft_putendl_fd("error, unexpected EOF while looking for matching \"", STDERR_FILENO);
		if (status == S_QUOTES)
			ft_putendl_fd("error, unexpected EOF while looking for matching \'", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCES);
}
