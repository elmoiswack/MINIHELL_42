#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	get_max_array(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (-1);
	while (array[index])
		index++;
	return (index);
}

int	ammount_of_words(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		while (line[index] && (line[index] != ' '))
			index++;
		count++;
		index = skip_spaces(line, index);
	}
	return (count);
}

int	skip_spaces(char *line, int index)
{
	while (line[index] && ((line[index] == ' ') \
		|| (line[index] == '\t') || (line[index] == '\n')))
		index++;
	return (index);
}

int	check_for_quotes(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '"')
		{
			return (1);
		}
		if (line[index] == 39)
		{
			return (1);
		}
		index++;
	}
	return (-1);
}

int	check_spaces_in_quotes(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '"' || line[index] == '\'')
		{
			index++;
			while (line[index] && (line[index] != '"' && line[index] != '\''))
			{
				if (line[index] == ' ')
					return (1);
				index++;
			}
			if (line[index] == '\0')
				return (-1);
		}
		if (line[index] != '\0')
			index++;
	}
	return (-1);
}
