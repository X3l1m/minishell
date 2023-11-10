#include <minishell.h>

void	init_cmd(t_commands **cmd)
{
	(*cmd)->com = NULL;
	(*cmd)->args = NULL;
	(*cmd)->next = NULL;
	(*cmd)->prev = NULL;
}
