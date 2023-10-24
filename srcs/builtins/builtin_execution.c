/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_execution.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:25:02 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/24 12:45:24 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

int	is_builtin(t_lexer *node)
{
	int	len;

	len = ft_strlen(node->content[0]);
	if (!node->content)
		return (NO_BUILTIN);
	else if (ft_strncmp(node->content[0], "exit", len) == 0)
		return (EXIT);
	else if (ft_strncmp(node->content[0], "echo", len) == 0)
		return (ECHO);
	else if (ft_strncmp(node->content[0], "cd", len) == 0)
		return (CD);
	else if (ft_strncmp(node->content[0], "pwd", len) == 0)
		return (PWD);
	else if (ft_strncmp(node->content[0], "env", len) == 0)
		return (ENV);
	else if (ft_strncmp(node->content[0], "export", len) == 0)
		return (EXPORT);
	else if (ft_strncmp(node->content[0], "unset", len) == 0)
		return (UNSET);
	else
		return (NO_BUILTIN);
}

int	execute_builtin(t_minishell *shell, t_builtin builtin, t_lexer *node)
{
	if (builtin == ECHO)
		return (execute_echo(shell->cmd_lst->content, shell->env_cpy,
				shell->status), 0);
	else if (builtin == CD)
		return (execute_cd(shell), 0);
	else if (builtin == PWD)
		return (execute_pwd(shell->env_cpy), 0);
	else if (builtin == ENV)
		return (execute_env(shell->env_cpy), 0);
	else if (builtin == EXPORT)
		return (execute_export(shell), 0);
	else if (builtin == UNSET)
		return (execute_unset(shell), 0);
	else if (builtin == EXIT)
		return (execute_exit(node));
	return (shell->status = 1, 1);
}
