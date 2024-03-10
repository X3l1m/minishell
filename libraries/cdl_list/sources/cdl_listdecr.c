/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listdecr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:04:20 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:04:21 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

// Shift down all elements of LIST by 1.
// The last element becomes the first one.
void	cdl_listdecr(t_dllist *list)
{
	list->head = list->head->prev;
}
