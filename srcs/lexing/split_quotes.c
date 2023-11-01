/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:28 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/01 18:03:52 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	get_len_quote(char *line, int index, char which)
{
	int	count;

	count = 0;
	while (line[index] && line[index] != which)
	{
		index++;
		count++;
	}
	while (line[index] && line[index] != ' ')
	{
		index++;
		count++;
	}
	return (count);
}

int	get_len_word(char *line, int index)
{
	int	count;

	count = 0;
	while (line[index] && line[index] != ' ')
	{
		if (line[index] == '=')
		{
			count++;
			count += get_len_quote(line, index + 2, '"') + 1;
			return (count);
		}
		index++;
		count++;
	}
	return (count);
}


int	get_len_next(char *line, int i_line)
{
	int	len;

	if (line[i_line] == '\'')
		len = get_len_quote(line, i_line + 1, '\'') + 1;
	else if (line[i_line] == '"')
		len = get_len_quote(line, i_line + 1, '"') + 1;
	else
		len = get_len_word(line, i_line);
	return (len);
}

char	**fill_array(char **split_array, char *line, int words)
{
	int	begin;
	int	i_sp;
	int	i_line;
	int	len;

	i_sp = 0;
	i_line = 0;
	while (line[i_line] && words > 0)
	{
		while (line[i_line] == ' ')
			i_line++;
		begin = i_line;
		len = get_len_next(line, i_line);
		split_array[i_sp] = ft_substr(line, begin, len);
		i_sp++;
		words--;
		i_line += len;
	}
	split_array[i_sp] = NULL;
	return (split_array);
}

char	**split_with_quotes(char *line, t_lexer *info_list)
{
	char	**split_array;
	int		words;

	words = ft_word_counter_quotations(line, ' ');
	split_array = ft_calloc(words + 1, sizeof(char *));
	if (!split_array)
		return (error_lex(info_list, 3, "split_quotes.c/L25"), NULL);
	split_array = fill_array(split_array, line, words);
	return (split_array);
}
