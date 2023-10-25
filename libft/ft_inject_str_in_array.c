/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_inject_str_in_array.c                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:49:02 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/25 18:51:02 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_inject_str_in_array(char **src, char *str, int index)
{
	char	**new;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = ft_arrlen(src);
	new = ft_calloc(size + 2, sizeof(char *));
	if (!new)
		return (src);
	while (j < size)
	{
		if (i == index)
		{
			new[i] = ft_strdup(str);
			j--;
		}
		else
			new[i] = ft_strdup(src[j]);
		if (!new[i])
			rev_free_arr(new, i);
		i++;
		j++;
	}
	free_double_array(src);
	return (new);
}
