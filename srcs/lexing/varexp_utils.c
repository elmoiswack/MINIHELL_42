/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:48:02 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/01 20:52:03 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_for_envvar(char **splitted_line)
{
	int	index;
	int	index_x;

	index = 0;
	while (splitted_line[index])
	{
		index_x = 0;
		while (splitted_line[index][index_x])
		{
			if (splitted_line[index][index_x] == '$')
			{
				index_x++;
				if (splitted_line[index][index_x] == '\0')
					break ;
				if (ft_isalpha(splitted_line[index][index_x]) == 1)
					return (1);
			}
			index_x++;
		}
		index++;
	}
	return (-1);
}

char	*get_variable_string(char *word_var, char *exp_var, int begin, int end)
{
	int	index;

	index = 0;
	while (begin < end)
	{
		exp_var[index] = word_var[begin];
		index++;
		begin++;
	}
	return (exp_var);
}

char	*remove_dollar_sign(char *old)
{
	char	*new;
	int		index_n;
	int		index_o;

	new = ft_calloc(ft_strlen(old), sizeof(char));
	if (!new)
		return (NULL);
	index_n = 0;
	index_o = 0;
	while (old[index_o])
	{
		if (old[index_o] != '$')
		{
			new[index_n] = old[index_o];
			index_n++;
		}
		index_o++;
	}
	free(old);
	return (new);
}

char	*get_expanded_variable(char *exp_var, char **env_cpy)
{
	char	*expanded;

	expanded = ft_getenv(exp_var, env_cpy);
	free(exp_var);
	return (expanded);
}
