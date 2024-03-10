/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 12:59:50 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 12:59:50 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_data_fd(t_commands *cmd)
{
	if (!cmd->fd_data)
	{
		cmd->fd_data = malloc(sizeof * cmd->fd_data);
		if (!cmd->fd_data)
			return ;
		cmd->fd_data->infile = NULL;
		cmd->fd_data->outfile = NULL;
		cmd->fd_data->delim_hd = NULL;
		cmd->fd_data->quotes_hd = false;
		cmd->fd_data->fd_in = -1;
		cmd->fd_data->fd_out = -1;
		cmd->fd_check = 1;
	}
}

void	add_shlvl(t_dllist *env)
{
	t_dlnode	*tmp;
	char		*ito;

	tmp = find_env(env, "SHLVL");
	if (!tmp)
	{
		tmp = cdl_nodenew(ft_strdup("SHLVL"), ft_strdup("1"));
		cdl_listaddback(env, tmp);
	}
	ito = ft_itoa(ft_atoi(tmp->value) + 1);
	free_pointer(tmp->value);
	tmp->value = ito;
}

bool	init_data(t_data *data, char **env)
{
	data->token = NULL;
	data->env = envcpy(env);
	add_shlvl(data->env);
	update_evn(data->env);
	if (!data->env)
		return (NULL);
	data->user_input = NULL;
	data->cmd = NULL;
	g_exit = 0;
	return (true);
}
