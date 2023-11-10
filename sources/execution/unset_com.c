#include <minishell.h>

int	unset_com(t_commands *cmd, t_dllist *env)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
		cdl_listdelnode(env, find_env(env, cmd->args[i]));
	return (update_evn(env));
}