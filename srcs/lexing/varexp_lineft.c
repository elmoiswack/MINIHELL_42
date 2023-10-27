/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_lineft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:40 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/27 16:17:25 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*get_variable(char *line, int begin, int end)
{
	char	*temp;
	int		index;

	temp = ft_calloc((end - begin) + 2, sizeof(char));
	if (!temp)
		return (NULL);
	index = 0;
	while (begin < end)
	{
		temp[index] = line[begin];
		index++;
		begin++;
	}
	return (temp);
}

char	*rm_quote_string_loop(char **splitted_line, int index, char *new_line)
{
	int	index_x;
	int	index_l;

	index_x = 0;
	index_l = 0;
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] != '"')
		{
			new_line[index_l] = splitted_line[index][index_x];
			index_l++;
		}
		index_x++;
	}
	return (new_line);
}

char	*remove_quotes_string(char **splitted_line, int index)
{
	char	*new_line;
	int		index_l;
	int		index_x;

	index_l = 0;
	index_x = 0;
	new_line = ft_calloc(ft_strlen(splitted_line[index]) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	if (splitted_line[index][0] == '"')
		new_line = rm_quote_string_loop(splitted_line, index, new_line);
	else
	{
		while (splitted_line[index][index_x])
		{
			if (splitted_line[index][index_x] != '\'')
			{
				new_line[index_l] = splitted_line[index][index_x];
				index_l++;
			}
			index_x++;
		}
	}
	free(splitted_line[index]);
	return (new_line);
}

char	*remove_dollar_sign(char *line)
{
	int		index_te;
	int		index_l;
	char	*temp;

	index_te = 0;
	index_l = 0;
	temp = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (line[index_l])
	{
		if (line[index_l] != '$')
		{
			temp[index_te] = line[index_l];
			index_te++;
		}
		index_l++;
	}
	return (temp);
}

char	*put_env_in_line(char *new_line, int index_l, \
	char **env_temp, int index_env)
{
	int	index_x;

	index_x = 0;
	if (env_temp[index_env] == NULL)
		return (new_line);
	while (env_temp[index_env][index_x])
	{
		new_line[index_l] = env_temp[index_env][index_x];
		index_l++;
		index_x++;
	}
	return (new_line);
}
