/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:53 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/06 14:37:44 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_whitespaces(char *line)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (line[index])
	{
		if (line[index] == ' ' || line[index] == '\t' \
			|| line[index] == '\v' || line[index] == '\n' \
			|| line[index] == '\f' || line[index] == '\r')
			count++;
		index++;
	}
	if (count == index)
		return (-1);
	return (1);
}

int	input_line_check(char *line, t_lexer *info_list)
{
	int	index;

	index = 0;
	if (check_whitespaces(line) == -1)
		return (error_lex(info_list, 2, "empty input!"), -1);
	if (check_for_quotes(line) == 1)
	{
		if (check_the_quotes(line) == -1)
			return (error_lex(info_list, 2, "unclosed quote!"), -1);
	}
	while (line[index])
	{
		if (line[index] == '"')
		{
			index++;
			while (line[index] && line[index] != '"')
				index++;
			if (line[index] == '\0')
				return (1);
		}
		if (line[index] == '\'')
		{
			index++;
			while (line[index] && line[index] != '\'')
				index++;
			if (line[index + 1] == '\0')
				return (1);
		}
		if (inputline_other_checks(line, info_list, index) == -1)
			return (-1);
		index++;
	}
	return (1);
}
