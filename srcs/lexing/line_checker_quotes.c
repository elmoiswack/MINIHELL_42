/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:35:22 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/10 14:02:45 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_only_quotes(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (ft_iswhitespace(line[index]) != 1 \
			&& (line[index] != '\'' && line[index] != '"'))
			return (-1);
		index++;
	}
	return (1);
}

int	input_check_quote(char *line, int *index, char which)
{
	int	i;

	i = *index;
	if (line[i] == which)
	{
		i++;
		while (line[i] && line[i] != which)
			i++;
		if (line[i] == '\0')
			return (1);
	}
	*index = i;
	return (-1);
}

int	check_quotes_loop(char *line, int index, int count, char c)
{
	index++;
	count++;
	while (line[index] && line[index] != c)
		index++;
	if (line[index] == c)
		count++;
	return (count);
}

int	check_the_quotes(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == '"')
		{
			count = check_quotes_loop(line, index, count, '"');
			index = get_end_quote(line, index, 1);
		}
		else if (line[index] == '\'')
		{
			count = check_quotes_loop(line, index, count, '\'');
			index = get_end_quote(line, index, 0);
		}
		if (index == -1)
			return (-1);
		if (line[index] != '\0')
			index++;
	}
	if (count % 2 == 0)
		return (1);
	return (-1);
}
