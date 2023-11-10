#include "../include/cdl_list.h"
#include <stdlib.h>

// add new node NODE to the front of LIST, and sets it as head
void	cdl_listaddfront(t_dllist *list, t_dlnode *node)
{
	cdl_listaddback(list, node);
	cdl_listdecr(list);
}
