#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*remove_spaces_quotes_line(char *line, char *new_line, \
	int index_n, int index_l)
{
	while (line[index_l])
	{
		new_line[index_n] = line[index_l];
		if (line[index_l] == '"' || line[index_l] == '\'')
		{
			index_n++;
			index_l++;
			while (line[index_l] && \
				(line[index_l] != '"' && line[index_l] != '\''))
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
	return (new_line);
}

char	*quote_data_inarray(char *line, char **temp, \
	int index_temp, int index_l)
{
	int	index_end;

	if (line[index_l] == '"')
		index_end = get_end_quote(line, index_l, 1);
	else
		index_end = get_end_quote(line, index_l, 0);
	if (index_end == -1)
	{
		free_double_array(temp);
		return (NULL);
	}
	temp[index_temp] = strcpy_splitquo(line, index_l, index_end);
	if (!temp[index_temp])
	{
		free_double_array(temp);
		return (NULL);
	}
	return (temp[index_temp]);
}

char	**store_all_quote_data(char *line, char **temp)
{
	int		index_l;
	int		index_temp;

	index_l = 0;
	index_temp = 0;
	while (line[index_l])
	{
		if (line[index_l] == '"' || line[index_l] == '\'')
		{
			temp[index_temp] = quote_data_inarray(line, temp, \
				index_temp, index_l);
			if (line[index_l] == '"')
				index_l = get_end_quote(line, index_l, 1);
			else
				index_l = get_end_quote(line, index_l, 0);
			index_temp++;
		}
		if (line[index_l] != '\0')
			index_l++;
	}
	temp[index_temp] = NULL;
	return (temp);
}
