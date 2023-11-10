/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohearn <ohearn@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 13:46:13 by ohearn        #+#    #+#                 */
/*   Updated: 2023/07/03 16:16:08 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_loop(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->user_input = readline("\033[0;35mMinishell$\033[0m ");
		set_signals_noninteractive();
		g_exit_code = parse_input_str(data);
		if (data->cmd)
			g_exit_code = executor(data->cmd, data->env);
		free_data(data, false);
	}
	return (0);
}
