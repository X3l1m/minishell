#include <minishell.h>

void	change_status_quote(t_token **list, int *i)
{
	if ((*list)->string[*i] == '\'')
		(*list)->status = S_QUOTES;
	else if ((*list)->string[*i] == '\"')
		(*list)->status = D_QUOTES;
	(*i)++;
}

/*Not sure this works the way I want it to*/
bool	change_status_default(t_token **list, int *i)
{
	if (((*list)->string[*i] == '\'' && (*list)->status == S_QUOTES)
		|| ((*list)->string[*i] == '\"' && (*list)->status == D_QUOTES))
	{
		(*list)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	return (false);
}

bool	change_status(t_token **list, int i)
{
	if (((*list)->string[i] == '\'' || (*list)->string[i] == '\"')
		&& (*list)->status == DEFAULT)
		return (true);
	return (false);
}

void	sort_strings(t_token **list, char *new)
{
	free_pointer((*list)->string);
	(*list)->string = new;
	//(*list)->join = true;
}
