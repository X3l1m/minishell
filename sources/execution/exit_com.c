#include <minishell.h>

bool check_max(int i, long num, short sg)
{
	if (num > LONG_MAX / 10)
		return (false);
	else if (num == LONG_MAX / 10)
		if ((i * sg) > LONG_MAX % 10
			|| (i * sg) < LONG_MIN % 10)
			return (false);
	return (true);
}

bool num_conv(char *str, int *exit_cod)
{
	int		i;
	long	num;
	short	sg;

	i = 0;
	sg = 1;
	num = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
	i++;
	if (str[i] == '-')
		sg = -sg;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!check_max(str[i] - 48, num, sg))
			return(false);
		num = (num * 10) + (str[i++] - 48);
	}
	num *= sg;
	num %= 256;
	*exit_cod = (int)num;
	return (true);
}

int	exit_com(t_data *data)
{
	int	exit_cod;

	exit_cod = 0;
	ft_putendl_fd("exit", 1);
	if (!data->cmd->args[1])
		free_data(data, true);
	if (!ft_istrdigit(data->cmd->args[1]) || !num_conv(data->cmd->args[1], &exit_cod))
	{
		g_exit = cmd_err_msg("exit", data->cmd->args[1], "numeric argument required", 2);
		free_data(data, true);
	}
	if (data->cmd->args[2])
		return(cmd_err_msg("exit", NULL, "too many arguments", 1));
	g_exit = exit_cod;
	free_data(data, true);
	return (0);
}
