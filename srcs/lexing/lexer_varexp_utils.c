#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_var_expander(char **splitted_line)
{
	int	index;

	index = 0;
	while (splitted_line[index])
	{
		if (splitted_line[index][0] == '$' \
			&& ft_isalpha(splitted_line[index][1]) == 1)
			return (1);
		if (splitted_line[index][0] == '"' && splitted_line[index][1] == '$' \
			&& ft_isalpha(splitted_line[index][2]) == 1)
			return (1);
		if (splitted_line[index][0] == 39 && splitted_line[index][1] == '$' \
			&& ft_isalpha(splitted_line[index][2]) == 1)
			return (1);
		index++;
	}
	return (-1);
}

char	*remove_dollar(char **splitted_line, int index)
{
	int		index_te;
	int		index_sp;
	char	*temp;

	index_te = 0;
	index_sp = 1;
	temp = ft_calloc(ft_strlen(splitted_line[index]), sizeof(char));
	if (!temp)
		return (NULL);
	while (splitted_line[index][index_sp])
	{
		temp[index_te] = splitted_line[index][index_sp];
		index_te++;
		index_sp++;
	}
	return (temp);
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

char	*remove_quotes_env(char **splitted_line, int index)
{
	char	*temp;
	int		index_tp;
	int		index_sp;

	index_tp = 0;
	index_sp = 0;
	temp = ft_calloc(ft_strlen(splitted_line[index]), sizeof(char));
	if (!temp)
		return (NULL);
	while (splitted_line[index][index_sp])
	{
		if (splitted_line[index][index_sp] != '"' && splitted_line[index][index_sp] != 39)
		{
			temp[index_tp] = splitted_line[index][index_sp];
			index_tp++;
		}
		index_sp++;
	}
	free(splitted_line[index]);
	return (temp);
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