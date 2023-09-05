#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*remove_dollar(char **splitted_line, int index)
{
	int		index_te;
	int		index_sp;
	char	*temp;

	index_te = 0;
	index_sp = 0;
	temp = ft_calloc(ft_strlen(splitted_line[index]) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (splitted_line[index][index_sp])
	{
		if (splitted_line[index][index_sp] != '$')
		{
			temp[index_te] = splitted_line[index][index_sp];
			index_te++;
		}
		index_sp++;
	}
	return (temp);
}

char	*remove_quotes_string(char **splitted_line, int index)
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
