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
