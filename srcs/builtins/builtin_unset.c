/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_unset.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:18:10 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 15:20:08 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	execute_unset(t_minishell *shell)
{
	int	var_index;
	int	i;

	var_index = 0;
	i = 1;
	if (shell->cmd_lst->content[1] == NULL)
	{
		g_exit_status = -1;
		return (error_unset_too_few_args());
	}
	while (shell->cmd_lst->content[i] && g_exit_status != 1)
	{
		var_index = var_exists(shell->env_cpy, shell->cmd_lst->content[i]);
		if (var_index >= 0)
		{
			shell->env_cpy = remove_str_from_array(shell->env_cpy, var_index);
			if (shell->env_cpy)
				g_exit_status = 0;
			else
				g_exit_status = 1;
		}
		i++;
	}
}
