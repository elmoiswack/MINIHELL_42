/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_arrayfts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:12 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/10 13:29:25 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (splitted_line[index][0] == '$' && splitted_line[index][1] == '?')
		return (FLAG);
	if (splitted_line[index][0] == '-' && ft_isalpha(splitted_line[index][1]))
		return (FLAG);
	if (splitted_line[index][0] == '\'' && ft_isalpha(splitted_line[index][1]))
		return (FLAG);
	if (ft_isdigit(splitted_line[index][0]) == 1)
		return (FLAG);
	if ((splitted_line[index][0] == '+') || (splitted_line[index][0] == '-') \
		|| (splitted_line[index][0] == '*'))
		return (FLAG);
	return (COMMAND);
}

int	into_enum_cases(char **splitted_line, int *enum_array, int index)
{
	if (ft_strncmp(splitted_line[index], "grep", ft_strlen("grep")) == 0)
	{
		index++;
		if (splitted_line[index] == NULL)
			return (0);
		if (is_metacharachter(splitted_line[index][0]) == -1)
		{
			enum_array[index] = FLAG;
			return (1);
		}
	}
	return (0);
}

int	*into_enum_array(char **splitted_line, int *enum_array, int index)
{
	while (splitted_line[index])
	{
		enum_array[index] = which_enum(splitted_line, index);
		if (into_enum_cases(splitted_line, enum_array, index) == 1)
			index++;
		else if (enum_array[index] == REDIRECT_IN)
		{
			index++;
			enum_array[index] = INFILE;
		}
		else if (enum_array[index] == REDIRECT_OUT)
		{
			index++;
			enum_array[index] = OUTFILE;
		}
		if (splitted_line[index])
		{
			index++;
		}
	}
	enum_array[index] = 0;
	return (enum_array);
}
