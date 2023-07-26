#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

//firstly split the vars in a 2d temp
//then expand the vars from the temp
//put all of the temp with strjoin in split[index]

char	**fill_2d_array_env(char **splitted_line, int index, char **temp)
{
	int	index_x;
	int	index_t;
	int	index_tx;
	int	end;

	index_x = 0;
	index_t = 0;
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == '$')
		{
			index_tx = 0;
			end = index_x + 1;
			while (splitted_line[index][end] && splitted_line[index][end] != '$')
				end++;
			temp[index_t] = ft_calloc(end - index_x + 2, sizeof(char));
			if (!temp[index_t])
				return (NULL);
			while (index_x < end)
			{
				temp[index_t][index_tx] = splitted_line[index][index_x];
				index_tx++;
				index_x++;
			}
		}
		if (splitted_line[index][index_x] != '$')
			index_x++;
		index_t++;
	}
	return (temp);
}

char	**one_line_multenv(char **splitted_line, int index)
{
	char	**temp;
	char	*temp_line;
	int		index_te;

	temp = ft_calloc(how_many_env(splitted_line, index) + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	temp = fill_2d_array_env(splitted_line, index, temp);
	if (!temp)
		return (NULL);
	index_te = 0;
	temp_line = ft_calloc(ft_strlen(temp[index_te]), sizeof(char));
	if (!temp_line)
		return (NULL);
	while (temp[index_te])
	{
		temp = one_case(temp, index_te);
		temp_line = ft_strjoin_and_free(temp_line, temp[index_te]);
		index_te++;
	}
	free_double_array(temp);
	free(splitted_line[index]);
	splitted_line[index] = temp_line;
	return (splitted_line);
}