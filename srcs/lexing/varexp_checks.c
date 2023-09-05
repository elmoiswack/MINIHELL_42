#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_env_in_string(char **splitted_line, int index)
{
	int	index_x;

	index_x = 0;
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == '$' \
			&& ft_isalpha(splitted_line[index][index_x + 1]) == 1)
			return (1);
		index_x++;
	}
	return (-1);
}

int	how_many_env(char **splitted_line, int index)
{
	int	index_x;
	int	count;

	count = 0;
	index_x = 0;
	while(splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == '$')
			count++;
		index_x++;
	}
	return (count);
}

int	check_multiple_env(char **splitted_line, int index)
{
	int	index_x;
	int	count;

	count = 1;
	index_x = 0;
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == '$')
			count--;
		if (count < 0)
			return (1);
		index_x++;
	}
	return (-1);
}

int	check_var_expander(char **splitted_line)
{
	int	index;
	int	index_x;

	index = 0;
	while (splitted_line[index])
	{
		index_x = 0;
		while (splitted_line[index][index_x])
		{
			if (splitted_line[index][index_x] == '$')
				return (1);
			index_x++;
		}
		index++;
	}
	return (-1);
}

int	are_there_spaces(char **splitted_line, int index)
{
	int	index_x;

	index_x = 0;
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == ' ')
			return (1);
		index_x++;
	}
	return (-1);
}
