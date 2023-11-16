/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_append_to_double_array.c                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:44:48 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/25 18:50:52 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_append_to_double_array(char **src, char *str)
{
	char	**new;
	int		n_of_arr;
	int		i;

	n_of_arr = 0;
	i = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 2);
	if (!new)
		return (src);
	while (i < n_of_arr)
	{
		new[i] = ft_strdup(src[i]);
		if (!new[i])
			rev_free_arr(new, i);
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		rev_free_arr(new, i);
	free_double_array(src);
	return (new);
}
