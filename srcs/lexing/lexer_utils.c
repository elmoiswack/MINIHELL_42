/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:37 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/06 15:23:47 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	get_max_array(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (-1);
	while (array[index])
		index++;
	return (index);
}

int	ammount_of_words(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		while (line[index] && (line[index] != ' '))
			index++;
		count++;
		index = skip_spaces(line, index);
	}
	return (count);
}

int	skip_spaces(char *line, int index)
{
	while (line[index] && ((line[index] == ' ') \
		|| (line[index] == '\t') || (line[index] == '\n')))
		index++;
	return (index);
}

int	check_for_quotes(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '"')
		{
			return (1);
		}
		if (line[index] == 39)
		{
			return (1);
		}
		index++;
	}
	return (-1);
}

int	is_metacharachter(char c)
{
	if (c == '<')
		return (1);
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	return (-1);
}
