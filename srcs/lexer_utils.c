#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int	ammount_of_words(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == ' ')
			count++;
		if (line[index] == '"')
		{
			index++;
			while (line[index] != '"')
				index++;
			count++;
		}
		index++;
	}
	count += 1;
	return (count);
}

int get_env_end(char *line, int index)
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
	while (line[index] && ((line[index] == ' ') || (line[index] == '\t') || (line[index] == '\n')))
		index++;
	return (index);	
}
//kdasdas