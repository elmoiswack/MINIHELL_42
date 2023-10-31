/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_exit.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:12:55 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/31 14:58:31 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	execute_exit(t_lexer *node)
{
	int	exit_code;

	exit_code = -1;
	if (!node->content[1])
	{
		if (!node->next)
		{
			ft_putstr_fd("exit\n", STDIN_FILENO);
			exit(0);
		}
		else
			exit(1);
	}
	else if (node->content[2])
		return (err_log(E_EXIT, "exit: too many arguments\n"));
	else if (node->content[1][0] == '-' && ft_isdigit(node->content[1][1]) == 0)
		return (err_log(E_EXIT, "exit: numeric argument required\n"));
	else if (ft_strisdigit(node->content[1]) || (node->content[1][0] == '-'
		&& ft_strisdigit(&node->content[1][1])))
	{
		exit_code = ft_atoi(node->content[1]);
		ft_putstr_fd("exit\n", STDIN_FILENO);
		exit(exit_code);
	}
	return (err_log(E_EXIT, "exit: numeric argument required\n"));
}
