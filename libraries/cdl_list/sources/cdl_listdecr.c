#include "../include/cdl_list.h"
#include <stdlib.h>

// Shift down all elements of LIST by 1.
// The last element becomes the first one.
void	cdl_listdecr(t_dllist *list)
{
	list->head = list->head->prev;
}
