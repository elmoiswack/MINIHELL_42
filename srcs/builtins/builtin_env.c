/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_env.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:12:23 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/25 15:51:39 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

int	execute_env(char *envp[], t_lexer *node)
{
	if (node->content[1])
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(node->content[1], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		return (127);
	}
	else
		print_double_array(envp);
	return (0);
}
