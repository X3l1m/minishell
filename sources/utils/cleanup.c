/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Owen <Owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 01:20:27 by Owen          #+#    #+#                 */
/*   Updated: 2023/09/01 10:08:34 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_pointer(void *pointer)
{
	if (pointer != NULL)
	{
		free(pointer);
		pointer = NULL;
	}
}

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free_pointer(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_data_fd(t_data_fd *io)
{
	if (!io)
		return ;
	free_pointer(io->delim_hd);
	free_pointer(io->infile);
	free_pointer(io->outfile);
	free_pointer(io);
}

void	free_data(t_data *data, bool clear_all)
{
	if (data && data->user_input)
	{
		free_pointer(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		lst_clear_tkn(&data->token, &free_pointer);
	if (data && data->cmd)
		lst_clear_cmd(&data->cmd, &free_pointer);
	if (clear_all == true)
	{
		free_dub(data->env->list);
		cdl_listclear(data->env);
		rl_clear_history();
		exit(0);
	}
}
