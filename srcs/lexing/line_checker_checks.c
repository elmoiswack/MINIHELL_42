/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:48 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/17 10:44:59 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_pipe(char *line, int index, t_lexer *info_list)
{
	int	temp;

	temp = index;
	while (temp > 0 && ft_isalpha(line[temp]) != 1)
		temp--;
	if (temp == 0 && ft_isalnum(line[temp]) != 1)
		return (error_lex(info_list, 2, \
			"something needs to be infront of the pipe!"), -1);
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

int	check_envvar(char *line, int index, t_lexer *info_list)
{
	if (index == 0)
		return (error_lex(info_list, 2, "missing an env_var name!"), -1);
	if (line[index - 1] && line[index - 1] == ' ')
		return (error_lex(info_list, 2, \
			"a space can't be infront of an '=' sign!"), -1);
	index--;
	while (line[index] && line[index] != ' ')
	{
		if (ft_isalnum(line[index]) != 1 && line[index] != '_')
			return (error_lex(info_list, 2, \
				"an env_var name can only exist \
			out of letters, numbers and a '_' sign!"), -1);
		index--;
		if (index == 0)
			break ;
	}
	index++;
	if (ft_isalpha(line[index]) != 1)
		return (error_lex(info_list, 2, \
			"an env_var name has to start with a letter of the alphabet!"), -1);
	return (1);
}
