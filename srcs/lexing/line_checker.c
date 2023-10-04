#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	inputline_other_checks(char *line, t_lexer *info_list, int index)
{
	if (line[index] == '<')
	{
		if (check_inredirect(line, index, info_list) == -1)
			return (-1);
	}
	if (line[index] == '>')
	{
		if (check_outredirect(line, index, info_list) == -1)
			return (-1);
	}
	if (line[index] == '|')
	{
		if (check_pipe(line, index, info_list) == -1)
			return (-1);
	}
	return (1);
}

int	input_line_check(char *line, t_lexer *info_list)
{
	int	index;
	int	quote_check;

	quote_check = -1;
	index = 0;
	while (line[index])
	{
		if (line[index] == '"' || line[index] == '\'')
		{
			if (quote_check == 1)
				quote_check = -1;
			else
			{
				quote_check = 1;
				if (check_quotes(line, index, info_list) == -1)
					return (-1);
			}
		}
		if (inputline_other_checks(line, info_list, index) == -1)
			return (-1);
		index++;
	}
	return (1);
}
