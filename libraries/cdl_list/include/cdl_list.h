/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_list.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:05:21 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:05:22 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CDL_LIST_H
# define CDL_LIST_H

# include <stddef.h>

// A singular node in the list. 
// Prev and Next point to the previous and next nodes in the list respectively
// Content is a pointer to the node's content
typedef struct s_dlnode
{
	struct s_dlnode	*prev;
	char			*name;
	char			*value;
	struct s_dlnode	*next;
}				t_dlnode;

// The list struct itself.
// listlen contains the amount of nodes in the list
// it is modified by my functions that add or remove nodes
//
// head points to the first entry of the list
typedef struct s_dllist
{
	int			listlen;
	char		**list;
	t_dlnode	*head;
	t_dlnode	*current;
}				t_dllist;

// add new node NODE to the back of LIST. If LIST is empty, it sets NODE as head
void		cdl_listaddback(t_dllist *list, t_dlnode *node);

// add new node NODE to the front of LIST, and sets it as head
void		cdl_listaddfront(t_dllist *list, t_dlnode *node);

// deletes and frees all node, and the list itself
void		cdl_listclear(t_dllist *list);

// Shift down all elements of LIST by 1.
// The last element becomes the first one.
void		cdl_listdecr(t_dllist *list);

// retuns a pointer to the N'th node of LIST (head is node 0).
// Because it is a circular list, it will loop around would N
// be greater than listlen. returns NULL if there are no nodes in the list
t_dlnode	*cdl_listgetnode(t_dllist *list, int n);

// Shift up all elements of LIST by 1.
// The first element becomes the last one.
void		cdl_listincr(t_dllist *list);

// creates and allocates a new list. Returns NULL if allocation fails
t_dllist	*cdl_listinit(void);

// remove given node from the list
void		cdl_listdelnode(t_dllist *list, t_dlnode *node);

// creates and allocates a new t_dlnode, using the given content
// the prev and next pointers are set to NULL
// On allocation failure, returns NULL
t_dlnode	*cdl_nodenew(char *n, char *v);

#endif