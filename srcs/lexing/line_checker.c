#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_pipe(char *line, int index, t_lexer *info_list)
{
	index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == '\0')
		return (set_error_lex(info_list, 2, "a command must follow a pipe!"), -1);
	if (is_metacharachter(line[index]) == 1)
		return (set_error_lex(info_list, 2, "a metacharacter can't follow a pipe!"), -1);
	return (1);
}

int	check_inredirect(char *line, int index, t_lexer *info_list)
{
	int	count;
	int	temp;

	count = 0;
	temp = index;
	while (line[index] && line[index] == '<')
	{
		index++;
		count++;
	}
	if (line[index] == '\0')
		return (set_error_lex(info_list, 2, "a file must follow a redirect in!"), -1);
	if (count > 2)
		return (set_error_lex(info_list, 2, "use of too many redirects!"), -1);
	index = temp;
	index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == '\0')
		return (set_error_lex(info_list, 2, "a file must follow a redirect in!"), -1);
	if (line[index] == '|' || line[index] == '>')
		return (set_error_lex(info_list, 2, "incorrect use of refirect in!"), -1);
	return (1);
}

int	check_outredirect(char *line, int index, t_lexer *info_list)
{
	int	count;
	int	temp;

	count = 0;
	temp = index;
	while (line[index] && line[index] == '>')
	{
		index++;
		count++;
	}
	if (line[index] == '\0')
		return (set_error_lex(info_list, 2, "a file must follow a redirect in!"), -1);
	if (count > 2)
		return (set_error_lex(info_list, 2, "use of too many redirects!"), -1);
	index = temp;
	index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == '\0')
		return (set_error_lex(info_list, 2, "a file must follow a redirect in!"), -1);
	if (line[index] == '|' || line[index] == '<')
		return (set_error_lex(info_list, 2, "incorrect use of refirect in!"), -1);
	return (1);
}

int	check_quotes(char *line, int index, t_lexer *info_list)
{
	index++;
	while (line[index])
	{
		if (line[index] == '"' || line[index] == '\'')
			return (1);
		index++;
	}
	return (set_error_lex(info_list, 2, "unclosed quotes!"), -1);
}

int	input_line_check(char *line, t_lexer *info_list)
{
	int	index;
	int	quote_check;

	quote_check = -1;
	index = 0;
	while (line[index])
	{
		if (line[index] == '|')
		{
			if (check_pipe(line, index, info_list) == -1)
				return (-1);
		}
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
		index++;
	}
	return (1);
}