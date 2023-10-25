/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   error.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:28:07 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/25 20:39:05 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

// printf("[%d]\n", __LINE__); __FILE__ TO PRINT LINE OR FILE

int	err_log(t_error err, char *input)
{
	if (err == E_ALLOC)
		return(ft_putstr_fd("malloc: could not allocate memory\n", STDERR_FILENO), E_ALLOC);
	else if (err == E_INPUT)
		return (ft_putstr_fd("executable can only be run as follows: './minishell'\n", STDERR_FILENO), E_INPUT);
	else if (err == E_IDENT)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	}
	else if (err == E_CMDNFND)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		return (ft_putstr_fd(": command not found\n", STDERR_FILENO), 127);
	}
	else if (err == E_FEWARG)
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
	return (err);
}
