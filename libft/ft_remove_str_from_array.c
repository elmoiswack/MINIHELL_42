/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_remove_str_from_array.c                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:48:33 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/25 18:51:08 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_remove_str_from_array(char **src, int index)
{
	char	**new;
	int		n_of_arr;
	int		i;
	int		j;

	n_of_arr = 0;
	i = 0;
	j = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	if (!new)
		return (src);
	while (i < (n_of_arr - 1) && src[j])
	{
		if (j == index)
			j++;
		if (j > n_of_arr)
			new[i] = ft_strdup(src[n_of_arr]);
		else
			new[i] = ft_strdup(src[j]);
		if (!new[i])
			rev_free_arr(new, i);
		i++;
		j++;
	}
	return (free_double_array(src), new);
}
