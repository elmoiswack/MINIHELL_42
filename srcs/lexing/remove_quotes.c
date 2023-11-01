#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*remove_single_quotes(char *word_var)
{
	int		index;
	char	*new_line;
	int		index_n;

	index = 0;
	index_n = 0;
	new_line = ft_calloc(ft_strlen(word_var), sizeof(char));
	if (!new_line)
		return (NULL);
	while (word_var[index])
	{
		if (word_var[index] != '\'')
		{
			new_line[index_n] = word_var[index];
			index_n++;
		}
		index++;
	}
	free(word_var);
	return (new_line);
}

char	*remove_double_quotes(char *word_var)
{
	int		index;
	char	*new_line;
	int		index_n;

	index = 0;
	index_n = 0;
	new_line = ft_calloc(ft_strlen(word_var), sizeof(char));
	if (!new_line)
		return (NULL);
	while (word_var[index])
	{
		if (word_var[index] != '"')
		{
			new_line[index_n] = word_var[index];
			index_n++;
		}
		index++;
	}
	free(word_var);
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
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] != '"' && splitted_line[index][index_x] != '\'')
		{
			new_line[index_l] = splitted_line[index][index_x];
			index_l++;
		}
		index_x++;
	}
	free(splitted_line[index]);
	return (new_line);
}