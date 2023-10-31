/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   err_log.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/26 12:38:57 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/31 14:53:20 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	error_command_not_found(char *cmd)
{
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	else
	 	ft_putstr_fd("n/a", STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

static int	error_export_invalid_identifier(char *input)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	if (input)
		ft_putstr_fd(input, STDERR_FILENO);
	else
	 	ft_putstr_fd("n/a", STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (1);
}

static void	error_allocation(char *input)
{
	ft_putstr_fd("malloc: could not allocate memory (", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd_nl(input, STDERR_FILENO);
		ft_putstr_fd_nl(")", STDERR_FILENO);
	}
	else
	 	ft_putstr_fd_nl(")", STDERR_FILENO);
}

int	err_log(t_error err, char *input)
{
	if (err == E_ALLOC)
		return (error_allocation(input), E_ALLOC);
	else if (err == E_INPUT)
		return (ft_putstr_fd("executable can only be run as follows:\
		'./minishell'\n", STDERR_FILENO), E_INPUT);
	else if (err == E_IDENT)
		return (error_export_invalid_identifier(input));
	else if (err == E_CMDNFND)
		return (error_command_not_found(input), 127);
	else if (err == E_EXIT)
		return (ft_putstr_fd(input, STDERR_FILENO), 1);
	return (err);
}
