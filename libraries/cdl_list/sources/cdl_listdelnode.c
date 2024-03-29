/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listdelnode.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:04:19 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:04:20 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

// remove given node from the list
void	cdl_listdelnode(t_dllist *list, t_dlnode *node)
{
	if (node == NULL)
		return ;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node->name);
	free(node->value);
	if (node == list->head)
	{
		if (node == node->next)
			list->head = NULL;
		else
			list->head = node->next;
	}
	free(node);
	list->listlen--;
}
