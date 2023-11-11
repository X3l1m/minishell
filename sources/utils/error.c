/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 16:50:47 by rmaes         #+#    #+#                 */
/*   Updated: 2023/07/03 15:51:00 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//if num is -1 program will exit with exit code 1
//if num exist return num after error message
int	error_mini(char *errmsg, int num)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (errno == 0)
		ft_putendl_fd(errmsg, STDERR_FILENO);
	else
		perror(errmsg);
	if (num < 0)
		exit(EXIT_FAILURE);
	else
		return(num);
}

static bool	need_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "unset", 6) == 0 || ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	return (false);
}

int	err_msg(char *com, char *msg, int err_nm)
{
	ft_putstr_fd(com, STDERR_FILENO);
	write(STDERR_FILENO, ": ", 2);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (err_nm);
}

int	cmd_err_msg(char *command, char *info, char *msg, int err)
{
	char	*err_msg;
	bool	quotes;

	quotes = need_quotes(command);
	err_msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		err_msg = join_str(err_msg, command);
		err_msg = join_str(err_msg, ": ");
	}
	if (info != NULL)
	{
		if (quotes == true)
			err_msg = join_str(err_msg, "`");
		err_msg = join_str(err_msg, info);
		if (quotes == true)
			err_msg = join_str(err_msg, "'");
		err_msg = join_str(err_msg, ": ");
	}
	err_msg = join_str(err_msg, msg);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	free_pointer(err_msg);
	return (err);
}

bool	print_error_msg(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (false);
}
