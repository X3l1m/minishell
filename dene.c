#include <stdio.h>
#include <stdlib.h>

char *ilk(void)
{
	char *dene = malloc(3);
	return(dene);
}

void son(char *ilk)
{
	free(ilk);
}


int	main()
{
	son(ilk());
}
