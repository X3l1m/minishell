/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listincr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:04:16 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:04:17 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

// Shift up all elements of LIST by 1.
// The first element becomes the last one.
void	cdl_listincr(t_dllist *list)
{
	list->head = list->head->next;
}
