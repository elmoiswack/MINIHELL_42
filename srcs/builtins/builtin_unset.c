/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_unset.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:18:10 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/26 13:17:45 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	execute_unset(t_minishell *shell)
{
	int	var_index;
	int	i;
	int	err;

	var_index = 0;
	i = 1;
	err = 0;
	if (shell->cmd_lst->content[1] == NULL)
		return (0);
	while (shell->cmd_lst->content[i])
	{
		var_index = var_exists(shell->env_cpy, shell->cmd_lst->content[i]);
		if (var_index >= 0)
		{
			shell->env_cpy = ft_remove_str_from_array(shell->env_cpy,
					var_index);
			if (shell->env_cpy)
				err = 0;
			else
				err = 1;
		}
		i++;
	}
	return (err);
}
