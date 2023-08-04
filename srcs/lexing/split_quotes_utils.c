#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	how_many_quotes(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == '"' || line[index] == '\'')
		{
			index++;
			while (line[index] && (line[index] != '"' && line[index] != '\''))
				index++;
			if (line[index] != '\0')
				count++;
		}
		if (line[index] != '\0')
			index++;
	}
	return (count);
}

int	get_end_quote(char *line, int end)
{
	end++;
	while (line[end])
	{
		if (line[end] == '"' || line[end] == '\'')
			return (end);
		end++;
	}
	return (-1);
}

char	*my_random_strcpy(char *line, int begin, int end) //I NEED A BETTER NAME FOR THIS FUNCTION!!!!!
{
	char	*temp;
	int		index;
	
	temp = ft_calloc(end - begin + 2, sizeof(char));
	if (!temp)
		return (NULL);
	index = 0;
	while (begin <= end)
	{
		temp[index] = line[begin];
		index++;
		begin++;
	}
	temp[index] = '\0';
	return (temp);
}
