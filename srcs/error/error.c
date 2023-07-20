#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	error_command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	error_export_invalid_identifier(char *input)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

void	error_unset_too_few_args()
{
	ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
}
//kdasdas
