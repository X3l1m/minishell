/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:02:53 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:02:53 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_cmd(t_commands **cmd)
{
	(*cmd)->com = NULL;
	(*cmd)->args = NULL;
	(*cmd)->next = NULL;
	(*cmd)->prev = NULL;
}
