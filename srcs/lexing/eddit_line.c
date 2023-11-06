/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eddit_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:08 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/06 14:34:28 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int	edit_line_cases(char *old, int index_o)
{
	if (old[index_o] == ' ')
		return (1);
	if ((is_metacharachter(old[index_o + 1]) == 1) \
		&& (old[index_o] != '<' && old[index_o] != '>'))
		return (1);
	if ((is_metacharachter(old[index_o]) == 1) \
		&& ((old[index_o + 1] == '$') \
		|| (ft_isalpha(old[index_o + 1]) == 1)))
		return (1);
	if ((is_metacharachter(old[index_o]) == 1) && (old[index_o + 1] && old[index_o + 1] == '"'))
		return (1);
	return (-1);
}

char	*quote_loop(char *new, char *old, int *index_o, char which)
{
	int	o_index;
	int	n_index;

	o_index = *index_o + 1;
	n_index = ft_strlen(new);
	while (old[o_index] && old[o_index] != which)
	{
		new[n_index] = old[o_index];
		n_index++;
		o_index++;
	}
	new[n_index] = old[o_index];
	if (old[o_index] != '\0')
		*index_o = o_index + 1;
	else
		*index_o = o_index;
	return (new);
}

char	*edit_line(char *old, char *new)
{
	int	index_n;
	int	index_o;

	index_n = 0;
	index_o = 0;
	while (old[index_o])
	{
		new[index_n] = old[index_o];
		if (old[index_o] == '"')
		{
			while (old[index_o] == '"')
			{
				new = quote_loop(new, old, &index_o, '"');
				index_n = ft_strlen(new) - 1;
				if (old[index_o] == '\0')
					return (new);
			}
		}
		else if (old[index_o] == '\'')
		{
			while (old[index_o] == '\'')
			{
				new = quote_loop(new, old, &index_o, '\'');
				index_n = ft_strlen(new) - 1;
				if (old[index_o] == '\0')
					return (new);
			}
		}
		if (edit_line_cases(old, index_o) == 1)
		{
			index_n++;
			new[index_n] = ' ';
		}
		index_n++;
		index_o++;
	}
	return (new);
}

char	*put_spaces_in_line(char *line, t_lexer *info_list)
{
	int		index;
	int		space_to_add;
	char	*temp;

	index = 0;
	space_to_add = 0;
	while (line[index])
	{
		if (is_metacharachter(line[index]) == 1)
			space_to_add += 2;
		index++;
	}
	temp = ft_calloc(index + space_to_add + 2, sizeof(char));
	if (!temp)
		return (error_lex(info_list, 3, "eddit_line.c/L73"), NULL);
	if (space_to_add == 0)
	{
		ft_strcpy(temp, line);
		return (temp);
	}
	temp = edit_line(line, temp);
	return (temp);
}