/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_del_2d.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/30 15:43:21 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/06/22 15:39:10 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_del_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}