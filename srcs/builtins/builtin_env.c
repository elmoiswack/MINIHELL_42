/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_env.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:12:23 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 15:12:30 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

void	execute_env(char *envp[])
{
	print_double_array(envp);
	g_exit_status = 0;
}
