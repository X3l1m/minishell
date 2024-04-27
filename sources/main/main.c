/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:00 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:01 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_exit = 0;

void	loop(t_data *data)
{
	t_commands	*tmp;

	while (1)
	{
		set_signals_interactive(0);
		data->user_input = readline("\033[0;35mminishell$\033[0m ");
		set_signals_noninteractive();
		if (parse_input_str(data))
		{
			g_exit = 1;
			ft_putendl_fd("Parse error!", STDERR_FILENO);
		}
		else if (data->cmd)
		{
			tmp = data->cmd;
			g_exit = executor(data);
			data->cmd = tmp;
		}
		free_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, env))
		exit(1);
	loop(&data);
	return (0);
}
