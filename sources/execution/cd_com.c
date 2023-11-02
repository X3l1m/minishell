#include <minishell.h>

int	cd_com(t_commands *cmd)
{
	if (cmd->args[2])
	{
		cmd_err_msg("cd", NULL, "too many arguments", 1);
		return (FAILURE);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		perror("cd");
		return (FAILURE);
	}
	return (SUCCES);
}

int	pwd_com(void)
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCES);
}

bool	check_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
		if (str[i++] != 'n')
			return (false);
	return (true);
}

int	echo_com(t_commands *cmd)
{
	int		i;
	bool	nl;
	if (!cmd->args[1])
		return (1);
	nl = false;
	if (cmd->args[1][0] == '-')
		nl = check_n(cmd->args[1]);
	i = nl;
	while (cmd->args[++i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			write(1, " ", 1);
	}
	if (!nl)
		write(1, "\n", 1);
	return (0);
}

int	export_com()
{
	return 0;
}