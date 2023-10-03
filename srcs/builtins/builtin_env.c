#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

void	execute_env(char *envp[], int fd)
{
	// print_double_array(envp);
	ft_putstr_fd_2d(envp, fd);
}

