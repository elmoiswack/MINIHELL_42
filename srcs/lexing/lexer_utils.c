#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	get_max_array(char **array)
{
	int	index;

	index = 0;
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

int	get_env_end(char *line, int index)
{
	while (line[index])
	{
		if (line[index] == ';')
			return (index);
		index++;
	}
	return (-1);
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
