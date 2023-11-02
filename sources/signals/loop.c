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
		if (parse_input_str(data) == true)
			printf("happy :D\n");
		// printf("%s\n", data->cmd->args[1]);
 		printf("\033[0;32m");
		if (data->user_input[0])
			executor(data->cmd, data->env);
		printf("\033[0m");
		// printf("%s\n", pathf(data->cmd->com, env));
		//printf("\033[32mloop:%s\033[0m\n", data->cmd->args[1]);
		// printf("loop:%d\n", data->cmd->fd_out);
		free_data(data, false);
	}
	return (0);
}
