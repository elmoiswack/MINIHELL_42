/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_copy_double_array.c                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:43:25 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/25 18:50:57 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_copy_double_array(char **array)
{
	char	**copy;
	int		n_of_arr;
	int		i;

	n_of_arr = 0;
	i = 0;
	while (array[n_of_arr])
		n_of_arr++;
	copy = ft_calloc(sizeof(char *), n_of_arr + 1);
	if (!copy)
		return (NULL);
	while (i < n_of_arr)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
			rev_free_arr(copy, i);
		i++;
	}
	return (copy);
}
