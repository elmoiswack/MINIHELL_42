#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*put_line_in_arr(char *line, int max, int begin_word)
{
	char	*arr_line;
	int		index;

	index = 0;
	arr_line = ft_calloc((max - begin_word) + 1, sizeof(char));
	if (!arr_line)
		return (NULL);
	while (begin_word < max)
	{
		arr_line[index] = line[begin_word];
		index++;
		begin_word++;
	}
	arr_line[index] = '\0';
	return (arr_line);
}

char	**super_split(char *line)
{
	int		index;
	int		index_y;
	int		begin_word;
	char	**arr;

	index = 0;
	begin_word = 0;
	index_y = 0;
	arr = ft_calloc((ammount_of_words(line) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (line[index])
	{
		if (line[index] == ' ')
		{
			arr[index_y] = put_line_in_arr(line, index, begin_word);
			if (!arr[index_y])
				return (free_2d_array(arr), NULL);
			index++;
			if (ft_isalpha(line[index]))
				begin_word = index;
			else
			{
				index = skip_spaces(line, index);
				begin_word = index;
			}
			index_y++;
		}
		if (line[index] == '"')
		{
			index = get_env_end(line, index);
			arr[index_y] = put_line_in_arr(line, index, begin_word);
			index++;
			if (ft_isalpha(line[index]))
				begin_word = index;
			else
			{
				index = skip_spaces(line, index);
				begin_word = index;
			}
			index_y++;		
		}
		index++;
	}
	arr[index_y] = put_line_in_arr(line, index, begin_word);
	if (!arr[index_y])
		return (free_2d_array(arr), NULL);
	index_y++;
	arr[index_y] = NULL;
	return (arr);
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

char	*edit_line(char *old, char *new)
{
	int	index_n;
	int	index_o;
	
	index_n = 0;
	index_o = 0;
	while (old[index_o])
	{
		new[index_n] = old[index_o];
		if ((is_metacharachter(old[index_o + 1]) == 1) && old[index_o] != '<')
		{
			index_n++;
			new[index_n] = ' ';	
		}
		if ((is_metacharachter(old[index_o]) == 1) && ((old[index_o + 1] == '$') || (ft_isalpha(old[index_o + 1]) == 1)))
		{
			index_n++;
			new[index_n] = ' ';
		}
		index_n++;
		index_o++;
	}
	new[index_n] = '\0';
	return (new);
}

char	*put_spaces_in_line(char *line)
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
	temp = ft_calloc(index + space_to_add + 1, sizeof(char));
	if (!temp)
		return (NULL);
	temp = edit_line(line, temp);
	free(line);
	return (temp);
}
//kdasdas