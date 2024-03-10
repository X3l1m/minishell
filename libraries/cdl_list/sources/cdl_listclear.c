/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listclear.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:04:22 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:04:22 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

// deletes and frees all nodes, and the list itself
void	cdl_listclear(t_dllist *list)
{
	while (list->head)
		cdl_listdelnode(list, list->head);
	free(list);
}
