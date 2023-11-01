/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_execution.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:25:02 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/01 13:54:18 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

int	is_builtin(t_lexer *node)
{
	if (!node->content)
		return (NO_BUILTIN);
	else if (ft_strncmp(node->content[0], "exit", 4) == 0)
		return (EXIT);
	else if (ft_strncmp(node->content[0], "echo", 4) == 0)
		return (ECHO);
	else if (ft_strncmp(node->content[0], "cd", 2) == 0)
		return (CD);
	else if (ft_strncmp(node->content[0], "pwd", 3) == 0)
		return (PWD);
	else if (ft_strncmp(node->content[0], "env", 3) == 0)
		return (ENV);
	else if (ft_strncmp(node->content[0], "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(node->content[0], "unset", 5) == 0)
		return (UNSET);
	else
		return (NO_BUILTIN);
}

int	execute_builtin(t_minishell *shell, t_builtin builtin, t_lexer *node)
{
	if (builtin == ECHO)
		return (execute_echo(shell->cmd_lst->content, shell->env_cpy,
				shell->status));
	else if (builtin == CD)
		return (execute_cd(shell, node, 0));
	else if (builtin == PWD)
		return (execute_pwd(shell->env_cpy));
	else if (builtin == ENV)
		return (execute_env(shell->env_cpy, node));
	else if (builtin == EXPORT)
		return (execute_export(shell, node));
	else if (builtin == UNSET)
		return (execute_unset(shell));
	else if (builtin == EXIT)
		return (execute_exit(node));
	return (shell->status = 1, 1);
}
