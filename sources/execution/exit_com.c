#include <minishell.h>


long long


int	exit_com(t_data *data)
{
	ft_putstr_fd("exit", 1);
	if (!data->cmd->args[1])
		free_data(data, true);
	num_conv();
	if (!ft_istrdigit(data->cmd->args[1]) || )
	{
		g_exit = cmd_err_msg("exit", data->cmd->args[1], "numeric argument required", 2);
		free_data(data, true);
	}
	if (data->cmd->args[2])
		return(cmd_err_msg("exit", NULL, "too many arguments", 1));

	g_exit = 
	
	return (0);
}
