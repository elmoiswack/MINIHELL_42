#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

int	is_builtin(t_lexer *node)
{
	if (!node->content)
		return (NO_BUILTIN);
	else if (ft_strncmp(node->content[0], "exit", ft_strlen(node->content[0])) == 0)
		return (EXIT);
	else if (ft_strncmp(node->content[0], "echo", ft_strlen(node->content[0])) == 0)
		return (ECHO);
	else if (ft_strncmp(node->content[0], "cd", ft_strlen(node->content[0])) == 0)
		return (CD);
	else if (ft_strncmp(node->content[0], "pwd", ft_strlen(node->content[0])) == 0)
		return (PWD);
	else if (ft_strncmp(node->content[0], "env", ft_strlen(node->content[0])) == 0)
		return (ENV);
	else if (ft_strncmp(node->content[0], "export", ft_strlen(node->content[0])) == 0)
		return (EXPORT);
	else if (ft_strncmp(node->content[0], "unset", ft_strlen(node->content[0])) == 0)
		return (UNSET);
	else
		return (NO_BUILTIN);
}

int	execute_builtin(t_minishell *shell, t_builtin builtin)
{
	if (builtin == ECHO)
		return (execute_echo(shell->cmd_lst->content, shell->env_cpy), 0);
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
		return (execute_exit(shell->cmd_lst));
	return (g_exit_status = 1, 1);
}
