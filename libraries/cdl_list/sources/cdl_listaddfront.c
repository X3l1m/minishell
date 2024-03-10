/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listaddfront.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:04:24 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:04:24 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

// add new node NODE to the front of LIST, and sets it as head
void	cdl_listaddfront(t_dllist *list, t_dlnode *node)
{
	cdl_listaddback(list, node);
	cdl_listdecr(list);
}
