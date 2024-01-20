#include <minishell.h>

int	mini_loop(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->user_input = readline("\033[0;35mminishell$\033[0m ");
		set_signals_noninteractive();
		if (parse_input_str(data))
			ft_putendl_fd("Parse error!", STDERR_FILENO);
		if (data->cmd)
			g_exit = executor(data);
		free_data(data, false);
	}
	return (0);
}
