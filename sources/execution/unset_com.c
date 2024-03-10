/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_com.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:25 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:25 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	unset_com(t_commands *cmd, t_dllist *env)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
		cdl_listdelnode(env, find_env(env, cmd->args[i]));
	return (update_evn(env));
}
