/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 12:59:55 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 12:59:56 by seyildir      ########   odam.nl         */
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

void	free_dub(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
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
	if (clear_all)
	{
		free_dub(data->env->list);
		cdl_listclear(data->env);
		rl_clear_history();
		exit(g_exit);
	}
}
