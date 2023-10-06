#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**replace_quotes_array(char **split_array, char	**temp_quotes)
{
	int	index;
	int	index_tmp;

	index = 0;
	index_tmp = 0;
	while (split_array[index])
	{
		if (split_array[index][0] == '"' || split_array[index][0] == '\'')
		{
			free(split_array[index]);
			split_array[index] = \
				ft_calloc(ft_strlen(temp_quotes[index_tmp]) + 1, sizeof(char));
			if (!split_array[index])
			{
				free_double_array(split_array);
				return (NULL);
			}
			ft_strcpy(split_array[index], temp_quotes[index_tmp]);
			index_tmp++;
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
		return (error_lex(info_list, 3, "split_quotes.c/L41"), NULL);
	}
	split_array = ft_split(temp_line, ' ');
	free(temp_line);
	if (!split_array)
	{
		free_double_array(temp_quotes);
		return (error_lex(info_list, 3, "split_quotes.c/L47"), NULL);
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
		return (error_lex(info_list, 3, "split_quotes.c/L65"), NULL);
	temp_quotes = store_all_quote_data(line, temp_quotes);
	if (!temp_quotes)
		return (error_lex(info_list, 2, "unclosed quotes!"), NULL);
	split_array = split_intoarray(line, info_list, temp_quotes);
	free_double_array(temp_quotes);
	return (split_array);
}
