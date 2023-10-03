#include "../../includes/minishell.h"
#include "../../libft/libft.h"
		
void	execute_unset(t_minishell *shell)
{
	int	var_index;

	var_index = 0;
	if (shell->cmd_lst->content[1] == NULL)
	{
		g_exit_status = -1;
		return (error_unset_too_few_args());
	}
	var_index = var_exists(shell->env_cpy, shell->cmd_lst->content[1]);
	if (var_index >= 0)
		shell->env_cpy = remove_str_from_array(shell->env_cpy, var_index);
}
