#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PWD_SIZE 256

static void pwd(char *cwd)
{
	int		cd_len;
	int		total_len;

	cd_len = ft_strlen(ft_strrchr(cwd, '/'));
	total_len = ft_strlen(cwd);
	write(1, cwd, total_len - cd_len);
	write(1, "\033[0;31m", 8);
	write(1, ft_strrchr(cwd, '/'), ft_strlen(ft_strrchr(cwd, '/')));
	write(1, "\033[0m\n", 6);
	g_exit_status = 0;
	free(cwd);
	return ;
}
void	execute_pwd(char *env_cpy[])
{
	char	*cwd;

	cwd = ft_getenv("PWD", env_cpy);
	if (!cwd)
	{
		g_exit_status = 1;
		return (perror("getcwd()"));
	}
	else
		return (pwd(cwd));
	if (getcwd(cwd, 256) == NULL)
	{
		g_exit_status = 1;
		return (perror("getcwd()"));
	}
	else
		return (pwd(cwd));
}


