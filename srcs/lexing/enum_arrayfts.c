#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	which_enum(char **splitted_line, int index)
{
	if (splitted_line[index][0] == '<' && splitted_line[index][1] != '<')
		return (REDIRECT_IN);
	if (splitted_line[index][0] == '<' && splitted_line[index][1] == '<')
		return (DELIMITER);
	if (splitted_line[index][0] == '>' && splitted_line[index][1] != '>')
		return (REDIRECT_OUT);
	if (splitted_line[index][0] == '>' && splitted_line[index][1] == '>')
		return (APPENDER);
	if (splitted_line[index][0] == '|')
		return (PIPE);
	if (splitted_line[index][0] == '$' && ft_isalpha(splitted_line[index][1]))
		return (ENV_VAR);
	if (splitted_line[index][0] == '-' && ft_isalpha(splitted_line[index][1]))
		return (FLAG);
	if (splitted_line[index][0] == '\'' && ft_isalpha(splitted_line[index][1]))
		return (FLAG);
	return (COMMAND);
}

int	*into_enum_array(char **splitted_line, int *enum_array, int index)
{
	while (splitted_line[index])
	{
		enum_array[index] = which_enum(splitted_line, index);
		if (enum_array[index] == REDIRECT_IN)
		{
			index++;
			enum_array[index] = INFILE;
		}
		else if (enum_array[index] == REDIRECT_OUT)
		{
			index++;
			enum_array[index] = OUTFILE;
		}
		index++;
	}
	enum_array[index] = 0;
	return (enum_array);
}