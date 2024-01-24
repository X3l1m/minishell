#include <minishell.h>

int	cd_com(t_commands *cmd)
{
	if (!cmd->args[1])
	{
		cmd_err_msg("cd", NULL, "no given arguments", 1);
		return (FAILURE);
	}
	if (cmd->args[2])
	{
		cmd_err_msg("cd", NULL, "too many arguments", 1);
		return (FAILURE);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		ft_putstr_fd("minishel: ", STDERR_FILENO);
		perror("cd");
		return (FAILURE);
	}
	return (SUCCES);
}
