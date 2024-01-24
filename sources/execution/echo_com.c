#include <minishell.h>

int	check_n(char **str)
{
	int	i;
	int	nl;

	nl = 1;
	while (str[nl][0] == '-')
	{
		i = 1;
		while (str[nl][i])
			if (str[nl][i++] != 'n')
				return (nl - 1);
		nl++;
	}
	return (nl - 1);
}

int	echo_com(t_commands *cmd)
{
	int		i;
	int		nl;

	if (!cmd->args[1])
	{
		write(1, "\n", 1);
		return (SUCCES);
	}
	nl = check_n(cmd->args);
	i = nl;
	while (cmd->args[++i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			write(1, " ", 1);
	}
	if (!nl)
		write(1, "\n", 1);
	return (SUCCES);
}