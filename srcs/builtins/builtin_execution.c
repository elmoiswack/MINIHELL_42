#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>

int	is_builtin(t_minishell *shell)
{
	if (ft_strncmp(shell->cmd_lst->content[0], "echo", 5) == 0 && shell->cmd_lst->output != OUTFILE)
		return (shell->builtin = ECHO, 1);
	else if (ft_strncmp(shell->cmd_lst->content[0], "cd", 3) == 0)
		return (shell->builtin = CD, 1);
	else if (ft_strncmp(shell->cmd_lst->content[0], "pwd", 4) == 0 && shell->cmd_lst->content[1] == NULL)
		return (shell->builtin = PWD, 1);
	else if (ft_strncmp(shell->cmd_lst->content[0], "env", 4) == 0 && shell->cmd_lst->content[1] == NULL)
		return (shell->builtin = ENV, 1);
	else if (ft_strncmp(shell->cmd_lst->content[0], "export", 7) == 0)
		return (shell->builtin = EXPORT, 1);
	else if (ft_strncmp(shell->cmd_lst->content[0], "unset", 7) == 0)
		return (shell->builtin = UNSET, 1);
	else if (ft_strncmp(shell->cmd_lst->content[0], "exit", 5) == 0 && shell->cmd_lst->content[1] == NULL)
		exit(0);
	else
		return (shell->builtin = NO_BUILTIN, -1);
}

int	execute_builtin(t_minishell *shell)
{
	if (shell->builtin == ECHO)
		return(execute_echo(shell->cmd_lst->content, &shell->status), 0);
	else if (shell->builtin == CD)
		return (execute_cd(shell), 0);
	else if (shell->builtin == PWD)
		return (execute_pwd(&shell->status), 0);
	else if (shell->builtin == ENV)
		return (execute_env(shell->env_cpy), 0);
	else if (shell->builtin == EXPORT)
		return (execute_export(shell), 0);
	else if (shell->builtin == UNSET)
		return (execute_unset(shell), 0);
	else if (shell->builtin == EXIT)
		exit(0);
	return (shell->status = 1, 1);
}
