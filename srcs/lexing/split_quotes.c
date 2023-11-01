/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:28 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/31 19:01:48 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*get_line_quote(char *word_var, char *temp_var)
{
	char *new;
	int	index_n;
	int	index_te;
	int	index;

	index = 0;
	index_n = 0;
	index_te = 0;
	new = ft_calloc(ft_strlen(word_var) + ft_strlen(temp_var), sizeof(char));
	if (!new)
	{
		free(word_var);
		return (NULL);
	}
	while (word_var[index] && word_var[index] != '"' && word_var[index] != '\'')
	{
		new[index_n] = word_var[index];
		index++;
		index_n++;
	}
	while (temp_var[index_te])
	{
		new[index_n] = temp_var[index_te];
		index_n++;
		index_te++;
	}
	index++;
	while (word_var[index] && word_var[index] != '"' && word_var[index] != '\'')
		index++;
	while (word_var[index])
	{
		new[index_n] = word_var[index];
		index_n++;
		index++;
	}
	free(word_var);
	return (new);
}

char	**replace_quotes_array(char **split_array, char	**temp_quotes)
{
	int	index;
	int	index_x;
	int	index_tmp;

	index = 0;
	index_tmp = 0;
	while (split_array[index])
	{
		index_x = 0;
		while (split_array[index][index_x])
		{
			if (split_array[index][index_x] == '"' || split_array[index][index_x] == '\'')
			{
				split_array[index] = get_line_quote(split_array[index], temp_quotes[index_tmp]);
				index_tmp++;
				break ;
			}
			index_x++;
		}
		index++;
	}
	return (split_array);
}

char	**split_intoarray(char *line, t_lexer *info_list, char **temp_quotes)
{
	char	**split_array;
	char	*temp_line;

	temp_line = ft_calloc(ft_strlen(line), sizeof(char));
	if (!temp_line)
		return (NULL);
	temp_line = remove_spaces_quotes_line(line, temp_line, 0, 0);
	if (!temp_line)
	{
		free_double_array(temp_quotes);
		return (error_lex(info_list, 3, "split_quotes.c/L53"), NULL);
	}
	split_array = ft_split(temp_line, ' ');
	free(temp_line);
	if (!split_array)
	{
		free_double_array(temp_quotes);
		return (error_lex(info_list, 3, "split_quotes.c/L59"), NULL);
	}
	split_array = replace_quotes_array(split_array, temp_quotes);
	return (split_array);
}

char	**split_with_quotes(char *line, t_lexer *info_list)
{
	char	**split_array;
	char	**temp_quotes;
	int		ammount_quotes;

	ammount_quotes = how_many_quotes(line);
	temp_quotes = ft_calloc(ammount_quotes + 1, sizeof(char *));
	if (!temp_quotes)
		return (error_lex(info_list, 3, "split_quotes.c/L77"), NULL);
	temp_quotes = store_all_quote_data(line, temp_quotes);
	if (!temp_quotes)
		return (error_lex(info_list, 3, "split_quotes.c/L80"), NULL);
	split_array = split_intoarray(line, info_list, temp_quotes);
	free_double_array(temp_quotes);
	return (split_array);
}
