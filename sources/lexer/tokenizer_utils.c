#include <minishell.h>

int	save_word(t_token **lst, char *str, int index, int start)
{
	int		i;
	char	*word;
	t_token	*new;

	i = 0;
	word = (char *)malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (error_mini("Malloc(tokenizer_utils: 24)", 1));
	while (start < index)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	new = new_token(word, ft_strdup(word), WORD, DEFAULT);
	if (!new)
		return (error_mini("Malloc(tokenizer_utils: 34)", 1));
	lst_add_back_tkn(lst, new);
	return (SUCCES);
}

char	*add_seperator(char *str, int index)
{
	int		i;
	char	*sep;

	sep = (char *)malloc(sizeof(char) * 3);
	if (!sep)
		return (NULL);
	i = 0;
	while (i < 2)
	{
		sep[i] = str[index];
		i++;
		index++;
	}
	sep[i] = '\0';
	return (sep);
}

int	save_seperator(t_token **lst, char *str, int index, int type)
{
	char	*sep;
	t_token	*new;

	if (type == HEREDOC || type == APPEND)
	{
		sep = add_seperator(str, index);
		if (!sep)
			return (error_mini("Malloc(tokenizer_utils: 50)", 1));
	}
	else
	{
		sep = (char *)malloc(sizeof(char) * 2);
		if (!sep)
			return (error_mini("Malloc(tokenizer_utils: 63)", 1));
		sep[0] = str[index];
		sep[1] = '\0';
	}
	new = new_token(sep, ft_strdup(sep), type, DEFAULT);
	if (!new)
		return (error_mini("Malloc(tokenizer_utils: 69)", 1));
	lst_add_back_tkn(lst, new);
	return (SUCCES);
}

int	id_type(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}

int	save_part(t_data *data, int *i, char *str, int start)
{
	int	type;

	type = id_type(str, (*i));
	if (type)
	{
		if ((*i) != 0 && id_type(str, (*i) - 1) == 0)
			save_word(&data->token, str, (*i), start);
		if (type == PIPE || type == INPUT || type == TRUNC
			|| type == HEREDOC || type == APPEND || type == END)
		{
			save_seperator(&data->token, str, (*i), type);
			if (type == HEREDOC || type == APPEND)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}
