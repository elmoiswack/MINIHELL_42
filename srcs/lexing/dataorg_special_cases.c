/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataorg_special_cases.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:38:57 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/25 16:04:32 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*special_case_files(t_lexer *info_list, char **splitted_line)
{
	int	index;

	index = get_max_array(splitted_line);
	info_list->content = ft_calloc(index + 1, sizeof(char *));
	if (!info_list->content)
		return (error_lex(info_list, 3, "dataorg_special_cases.c/L49"), NULL);
	index = 0;
	while (splitted_line[index])
	{
		info_list->content[index] = \
			ft_calloc(ft_strlen(splitted_line[index]) + 1, sizeof(char));
		if (!info_list->content[index])
			return (error_lex(info_list, 3, \
				"dataorg_special_cases.c/L55"), NULL);
		ft_strcpy(info_list->content[index], splitted_line[index]);
		index++;
	}
	info_list->content[index] = NULL;
	info_list->path = get_path_of_command(info_list->content[0], \
		info_list->env_copy);
	info_list->next = NULL;
	info_list->input = NONE;
	info_list->output = NONE;
	return (info_list);
}

t_lexer	*other_special_case(t_lexer	*info_list, char **splitted_line, \
	int *enum_array, int index)
{
	if ((ft_strncmp(splitted_line[0], "mkdir", \
		ft_strlen(splitted_line[0])) == 0) \
		|| (ft_strncmp(splitted_line[0], "touch", \
			ft_strlen(splitted_line[0])) == 0)
		|| (ft_strncmp(splitted_line[0], "rm", ft_strlen(splitted_line[0])) == 0))
	{
		info_list = special_case_files(info_list, splitted_line);
		free_double_array(splitted_line);
		free(enum_array);
		return (info_list);
	}
	while (enum_array[index] == COMMAND)
		index++;
	if (enum_array[index] == 0)
		return (intolist_commands(info_list, splitted_line, enum_array));
	return (NULL);
}

t_lexer	*which_special_case(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	if (ft_strncmp(splitted_line[0], "echo", ft_strlen(splitted_line[0])) == 0)
	{
		while (splitted_line[index])
		{
			if (is_metacharachter(splitted_line[index][0]) == 1)
			{
				info_list = echo_with_meta(info_list, \
					splitted_line, enum_array);
				free_double_array(splitted_line);
				free(enum_array);
				return (info_list);
			}
			index++;
		}
		info_list = special_case_echo(info_list, splitted_line);
		free(enum_array);
		return (info_list);
	}
	info_list = other_special_case(info_list, splitted_line, enum_array, 0);
	if (!info_list)
		return (NULL);
	info_list = check_quotes_list(info_list);
	return (info_list);
}

int	check_special_cases(char **splitted_line, int *enum_array)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	if (ft_strncmp(splitted_line[0], "echo", ft_strlen(splitted_line[0])) == 0)
		return (1);
	if (ft_strncmp(splitted_line[0], "rm", ft_strlen(splitted_line[0])) == 0)
		return (1);
	if (ft_strncmp(splitted_line[0], "mkdir", ft_strlen(splitted_line[0])) == 0)
		return (1);
	if (ft_strncmp(splitted_line[0], "touch", ft_strlen(splitted_line[0])) == 0)
		return (1);
	while (splitted_line[index])
	{
		if (enum_array[index] == COMMAND)
			count++;
		index++;
	}
	if (count == index)
		return (1);
	return (-1);
}
