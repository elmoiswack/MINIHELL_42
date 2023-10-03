#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*remove_spaces_quotes_line(char *line)
{
	char	*new_line;
	int		index_n;
	int		index_l;

	index_n = 0;
	index_l = 0;
	new_line = ft_calloc(ft_strlen(line), sizeof(char));
	if (!new_line)
		return (NULL);
	while (line[index_l])
	{
		new_line[index_n] = line[index_l];
		if (line[index_l] == '"' || line[index_l] == '\'')
		{
			index_n++;
			index_l++;
			while (line[index_l] && (line[index_l] != '"' && line[index_l] != '\''))
			{
				if (line[index_l] != ' ')
				{
					new_line[index_n] = line[index_l];
					index_n++;
				}
				index_l++;
			}
			new_line[index_n] = line[index_l];
		}
		index_n++;
		index_l++;
	}
	free(line);
	return (new_line);
}

char	**store_all_quote_data(char *line, char **temp)
{
	int		index_l;
	int		index_end;
	int		index_temp;

	index_l = 0;
	index_temp = 0;
	while (line[index_l])
	{
		if (line[index_l] == '"' || line[index_l] == '\'')
		{
			if (line[index_l] == '"')
				index_end = get_end_quote(line, index_l, 1);
			else
				index_end = get_end_quote(line, index_l, 0);
			if (index_end == -1)
			{
				free_double_array(temp);
				return (NULL);
			}
			temp[index_temp] = my_random_strcpy(line, index_l, index_end); //I NEED A BETTER NAME FOR THE STRCPY FUNCT
			if (!temp[index_temp])
			{
				free_double_array(temp);
				return (NULL);
			}
			index_l = index_end;
			index_temp++;
		}
		if (line[index_l] != '\0')
		index_l++;
	}
	temp[index_temp] = NULL;
	return (temp);
}

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
			split_array[index] = ft_calloc(ft_strlen(temp_quotes[index_tmp]) + 1, sizeof(char));
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

char	**split_with_quotes(char *line, t_lexer *info_list)
{
	char	**split_array;
	char	**temp_quotes;
	char	*temp_line;
	int		ammount_quotes;

	ammount_quotes = how_many_quotes(line);
	temp_quotes = ft_calloc(ammount_quotes + 1, sizeof(char *));
	if (!temp_quotes)
		return (set_error_lex(info_list, 3, "split_quotes.c/L97"), NULL);
	temp_quotes = store_all_quote_data(line, temp_quotes);
	if (!temp_quotes)
		return (set_error_lex(info_list, 2, "unclosed quotes!"), NULL);
	temp_line = remove_spaces_quotes_line(line);
	if (!temp_line)
	{
		free_double_array(temp_quotes);
		return (set_error_lex(info_list, 3, "split_quotes.c/L14"), NULL);
	}
	split_array = ft_split(temp_line, ' ');
	free(temp_line);
	if (!split_array)
	{
		free_double_array(temp_quotes);
		return (set_error_lex(info_list, 3, "split_quotes.c/L104"), NULL);
	}
	split_array = replace_quotes_array(split_array, temp_quotes);
	free_double_array(temp_quotes);
	return (split_array);
}
