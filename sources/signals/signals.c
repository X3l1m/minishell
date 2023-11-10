/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 13:59:44 by Owen          #+#    #+#                 */
/*   Updated: 2023/07/03 15:50:52 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Resets the readline user input prompt*/
void	reset(int	temp)
{
	(void)temp;
	write (1, "\n", 1);
	g_exit_code = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*Prints a newline when a signal is caught*/
void	s_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	set_signals_interactive(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal36");
	if (signal(SIGINT, reset) == SIG_ERR)
		perror("signal38");
}

void	set_signals_noninteractive(void)
{
	if (signal(SIGINT, s_newline) == SIG_ERR)
	{
		perror("signal45");
		exit(FAILURE);
	}
	if (signal(SIGQUIT, s_newline) == SIG_ERR)
	{
		perror("signal50");
		exit(FAILURE);
	}
}
