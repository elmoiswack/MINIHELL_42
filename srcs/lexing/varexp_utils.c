/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:43 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/23 15:40:44 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	how_many_env_var(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == '$')
		{
			if (line[index + 1] != '\0' && line[index + 1] != '?')
				count++;
		}
		index++;
	}
	return (count);
}

int	get_env_end(char *line, int index)
{
	while (line[index])
	{
		if (ft_isalpha(line[index]) != 1)
			return (index);
		index++;
	}
	return (index);
}

int	get_size_strings(char *line, char **env_temp)
{
	int	size;
	int	index;

	index = 0;
	size = ft_strlen(line);
	while (env_temp[index])
	{
		size += ft_strlen(env_temp[index]);
		index++;
	}
	return (size);
}

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
