#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

//ASCII VALUE OF ' IS 39

int	check_for_quotes(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '"')
		{
			if (line[index - 1] == ' ')
				return (1);
		}
		if (line[index] == 39)
		{
			if (line[index - 1] == ' ')
				return (1);
		}
		index++;
	}
	return (-1);
}

char	*store_quote_data(char *line, int index_line, int end)
{
	int		index_temp;
	char	*temp;

	index_temp = 0;
	temp = ft_calloc(end - index_line + 2, sizeof(char));
	if (!temp)
		return (NULL);
	while (index_line <= end)
	{
		temp[index_temp] = line[index_line];
		index_temp++;
		index_line++;
	}
	temp[index_temp] = '\0';
	return (temp);
}

char	*finish_temp_rmsp(char *line, int index_line, char *temp, int index)
{
	while (line[index_line] != '"' && line[index_line] != 39)
	{
		while (line[index_line] == ' ')
			index_line++;
		temp[index] = line[index_line];
		index++;
		index_line++;
	}
	while (line[index_line])
	{
		temp[index] = line[index_line];
		index++;
		index_line++;
	}
	temp[index] = '\0';
	return (temp);
}

char	*remove_spaces_quote(char *line)
{
	int		index;
	int		index_line;
	char	*temp;

	index = 0;
	index_line = 0;
	temp = ft_calloc(ft_strlen(line), sizeof(char));
	if (!temp)
		return (NULL);
	while (line[index_line] != '"' && line[index_line] != 39)
	{
		temp[index] = line[index_line];
		index++;
		index_line++;
	}
	temp[index] = line[index_line];
	index++;
	index_line++;
	temp = finish_temp_rmsp(line, index_line, temp, index);
	free(line);
	return (temp);
}

char	**split_with_quotes(char *line)
{
	int		index_line;
	int		end;
	int		index;
	char	*temp;
	char	**split_arr;

	index_line = 0;
	end = 0;
	index = 0;
	while (line[index_line] \
		&& (line[index_line] != '"' && line[index_line] != 39))
		index_line++;
	if (line[index_line] == '\0')
		return (NULL);
	end = index_line;
	end++;
	while (line[end] && (line[end] != '"' && line[end] != 39))
		end++;
	if (line[end] == '\0')
		return (NULL);
	temp = store_quote_data(line, index_line, end);
	if (!temp)
		return (NULL);
	line = remove_spaces_quote(line);
	if (!line)
		return (NULL);
	split_arr = ft_split(line, ' ');
	if (!split_arr)
		return (NULL);
	while (split_arr[index][0] != '"' && split_arr[index][0] != 39)
		index++;
	free(split_arr[index]);
	split_arr[index] = temp;
	return (split_arr);
}
