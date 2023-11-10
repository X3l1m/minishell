#include "../include/cdl_list.h"
#include <stdlib.h>

// deletes and frees all nodes, and the list itself
void	cdl_listclear(t_dllist *list)
{
	while (list->head)
		cdl_listdelnode(list, list->head);
	free(list);
}
