#include "../include/cdl_list.h"
#include <stdlib.h>

// creates and allocates a new list. Returns NULL if allocation fails
t_dllist	*cdl_listinit(void)
{
	t_dllist	*list;

	list = malloc(sizeof(t_dllist));
	if (list == NULL)
		return (NULL);
	list->head = NULL;
	list->current = NULL;
	list->list = NULL;
	list->listlen = 0;
	return (list);
}
