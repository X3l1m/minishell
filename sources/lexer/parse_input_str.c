#include <minishell.h>

bool	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
			i++;
		else
			return (false);
	}
	return (true);
}

void	last_com(t_commands *cmd, t_dllist *env)
{
	int			i;
	char		*last;
	t_dlnode	*tmp;

	i = -1;
	tmp = find_env(env, "_");
	if (!tmp)
		return ;
	if (cmd->pipe)
		return ;
	while (cmd->args[++i])
	{
		if (!cmd->args[i + 1])
		{
			last = ft_strdup(cmd->args[i]);
			if (!last)
				return (ft_putstr_fd("malloc fail: last_com", STDERR_FILENO));
			break ;
		}
	}
	free(tmp->value);
	tmp->value = last;
	update_evn(env);
}

int	parse_input_str(t_data *data)
{
	if (data->user_input == NULL)
		free_data(data, true);
	else if (!data->user_input[0])
		return (SUCCES);
	else if (is_space(data->user_input) == true)
		return (SUCCES);
	add_history(data->user_input);
	if (tokenizer(data, data->user_input))
		return (FAILURE);
	if (data->token->type == END)
		return (FAILURE);
	if (check_for_var(&data->token) == false)
		return (FAILURE);
	if (expand_var(data, &data->token))
		return (FAILURE);
	if (data->token->type != END)
		parse_data(data, data->token);
	last_com(data->cmd, data->env);
	return (SUCCES);
}
