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
		return (error_lex(info_list, 2, \
			"a command must follow a pipe!"), -1);
	if (is_metacharachter(line[index]) == 1)
		return (error_lex(info_list, 2, \
			"a metacharacter can't follow a pipe!"), -1);
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
		return (error_lex(info_list, 2, \
			"a file must follow a redirect in!"), -1);
	if (count > 2)
		return (error_lex(info_list, 2, \
			"use of too many redirects!"), -1);
	index = temp + 1;
	while (line[index] == ' ')
		index++;
	if (line[index] == '\0')
		return (error_lex(info_list, 2, \
			"a file must follow a redirect in!"), -1);
	if (line[index] == '|' || line[index] == '>')
		return (error_lex(info_list, 2, "incorrect use of refirect in!"), -1);
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
		return (error_lex(info_list, 2, \
			"a file must follow a redirect out!"), -1);
	if (count > 2)
		return (error_lex(info_list, 2, \
			"use of too many redirects!"), -1);
	index = temp + 1;
	while (line[index] == ' ')
		index++;
	if (line[index] == '\0')
		return (error_lex(info_list, 2, \
			"a file must follow a redirect out!"), -1);
	if (line[index] == '|' || line[index] == '<')
		return (error_lex(info_list, 2, "incorrect use of refirect out!"), -1);
	return (1);
}

int	check_quotes_loop(char *line, int index, int count, char c)
{
	index++;
	count++;
	while (line[index] && line[index] != c)
		index++;
	if (line[index] == c)
		count++;
	return (count);
}

int	check_the_quotes(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == '"')
		{
			count = check_quotes_loop(line, index, count, '"');
			index = get_end_quote(line, index, 1);
		}
		if (line[index] == '\'')
		{
			count = check_quotes_loop(line, index, count, '\'');
			index = get_end_quote(line, index, 0);
		}
		if (index == -1)
			return (-1);
		if (line[index] != '\0')
			index++;
	}
	if (count % 2 == 0)
		return (1);
	return (-1);
}
