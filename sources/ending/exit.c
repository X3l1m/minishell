#include <minishell.h>

/*Exits the shell and frees the data struct*/
void	exit_ms(t_data *data, int num)
{
	if (data)
	{
		free_data(data, false);
	}
	exit(num);
}
