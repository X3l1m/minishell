#include "../include/cdl_list.h"
#include <stdlib.h>

// Shift up all elements of LIST by 1.
// The first element becomes the last one.
void	cdl_listincr(t_dllist *list)
{
	list->head = list->head->next;
}
