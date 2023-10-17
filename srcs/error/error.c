#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	error_command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

void	error_export_invalid_identifier(char *input)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

void	error_unset_too_few_args(void)
{
	ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
}

void	error_lexing_message(t_lexer *list)
{
	if (list->error_code == 1)
		printf("%s\n", list->error_str);
	if (list->error_code == 2)
		printf("Syntax error, %s\n", list->error_str);
	if (list->error_code == 3)
		printf("Allocation error at %s\n", list->error_str);
}

int	error_exit(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (1);
}
