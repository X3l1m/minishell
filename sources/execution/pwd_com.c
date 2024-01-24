#include <minishell.h>

int	pwd_com(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (errno);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (SUCCES);
}
