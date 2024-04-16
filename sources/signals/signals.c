/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 12:59:57 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 12:59:57 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reset(int temp)
{
	(void)temp;
	write (1, "\n", 1);
	g_exit = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	s_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	exit_heredoc(int temp)
{
	(void)temp;
	g_exit++;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	set_signals_interactive(int heredoc)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal 40");
	if (heredoc)
	{
		if (signal(SIGINT, exit_heredoc) == SIG_ERR)
			perror("signal 44");
	}
	else
	{
		if (signal(SIGINT, reset) == SIG_ERR)
			perror("signal 49");
	}
}

void	set_signals_noninteractive(void)
{
	if (signal(SIGINT, s_newline) == SIG_ERR)
	{
		perror("signal 57");
		exit(FAILURE);
	}
	if (signal(SIGQUIT, s_newline) == SIG_ERR)
	{
		perror("signal 62");
		exit(FAILURE);
	}
}
