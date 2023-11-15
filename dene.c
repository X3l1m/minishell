#include <stdio.h>
#include <stdlib.h>

char *ilk(void)
{
	char *dene = malloc(3);
	return(dene);
}

void son(char **str)
{
	*str = malloc(5);
	for (int i = 0; i < 4; i++)
	{
		*str[i] = 'a';
	}
	*str[4] = 0;
}


int	main()
{
	char *str;
	son(&str);
	printf("%s\n", str);
}
