/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_env.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:12:23 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/24 12:23:27 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

int	execute_env(char *envp[])
{
	print_double_array(envp);
	return (0);
}
