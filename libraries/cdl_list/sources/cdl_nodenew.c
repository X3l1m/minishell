/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_nodenew.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:04:14 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:04:15 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

// creates and allocates a new t_dlnode, using the given content
// the prev and next pointers are set to NULL
// On allocation failure, returns NULL
t_dlnode	*cdl_nodenew(char *n, char *v)
{
	t_dlnode	*node;

	node = malloc(sizeof(t_dlnode));
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->name = n;
	node->value = v;
	return (node);
}
