#include <minishell.h>

int	g_exit = 0;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, env))
		exit(1);
	mini_loop(&data);
	return (0);
}
