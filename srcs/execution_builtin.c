#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

int	is_builtin(char **raw_input, int *builtin)
{
	if (ft_strncmp(raw_input[0], "echo", 5) == 0)
		return (*builtin = ECHO, 1);
	else if (ft_strncmp(raw_input[0], "cd", 3) == 0)
		return (*builtin = CD, 1);
	else if (ft_strncmp(raw_input[0], "pwd", 4) == 0 && raw_input[1] == NULL)
		return (*builtin = PWD, 1);
	else if (ft_strncmp(raw_input[0], "env", 4) == 0 && raw_input[1] == NULL)
		return (*builtin = ENV, 1);
	else if (ft_strncmp(raw_input[0], "exit", 5) == 0 && raw_input[1] == NULL)
		exit(0);
	else
		return (*builtin = NO_BUILTIN, -1);
}

void	execute_builtin(char **raw_input, char *envp[], int builtin, int *exit_status)
{
	if (builtin == ECHO)
		return(execute_echo(raw_input, exit_status));
	else if (builtin == CD)
		return (execute_cd(raw_input, exit_status));
	else if (builtin == PWD)
		return (execute_pwd());
	else if (builtin == ENV)
		return (execute_env(envp));
	else if (builtin == EXIT)
		exit(0);
}