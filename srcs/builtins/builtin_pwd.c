#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <unistd.h>

void	execute_pwd(void)
{
	char	cwd[256];
	int		cd_len;
	int		total_len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd()");
		g_exit_status = 1;
		return ;
	}
	else
	{
		cd_len = ft_strlen(ft_strrchr(cwd, '/'));
		total_len = ft_strlen(cwd);
		write(1, cwd, total_len - cd_len);
		write(1, "\033[0;31m", 8);
		write(1, ft_strrchr(cwd, '/'), ft_strlen(ft_strrchr(cwd, '/')));
		write(1, "\033[0m\n", 6);
		g_exit_status = 0;
		return ;
	}
}
