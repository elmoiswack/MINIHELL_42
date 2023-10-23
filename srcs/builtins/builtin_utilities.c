/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_utilities.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:22:10 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 15:26:46 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdbool.h>

bool	is_relative_path(char *content)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i] && content[j])
	{
		if (ft_strncmp(&content[i], "../", 3) == 0)
			i += 3;
		else
			return (false);
		j++;
	}
	return (true);
}
