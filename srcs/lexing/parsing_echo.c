/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:04 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/09 17:53:11 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*default_echo_data(t_lexer *info_list, char **splitted_line)
{
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->path = get_path_of_command(splitted_line[0], \
		info_list->env_copy);
	return (info_list);
}

t_lexer	*echo_meta_intolist(t_lexer *info_list, \
	char **splitted_line, int *enum_array, int index)
{
	while (splitted_line[index] && \
		is_metacharachter(splitted_line[index][0]) != 1)
	{
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
			splitted_line[index]);
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "parsing_echo.c/L37"), NULL);
		if (splitted_line[index + 1] != NULL && is_metacharachter(splitted_line[index + 1][0]) != 1)
			info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
				" ");
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "parsing_echo.c/L42"), NULL);
		index++;
	}
	info_list = organizing_data(info_list, splitted_line, enum_array, index);
	return (info_list);
}

t_lexer	*echo_with_meta(t_lexer *info_list, char **splitted_line, \
	int *enum_array)
{
	int	index;

	index = 1;
	info_list = default_echo_data(info_list, splitted_line);
	info_list->content = allocate_2d_arr(ft_strlen(splitted_line[0]) + 1, \
		info_list);
	if (!info_list->content)
		return (error_lex(info_list, 3, "parsing_echo.c/L59"), NULL);
	ft_strcpy(info_list->content[0], splitted_line[0]);
	info_list->content[1] = ft_calloc(1, sizeof(char));
	if (!info_list->content[1])
		return (error_lex(info_list, 3, "parsing_echo.c/L64"), NULL);
	info_list = echo_meta_intolist(info_list, splitted_line, enum_array, index);
	return (info_list);
}

t_lexer	*spca_echo_intolist(t_lexer *info_list, char **splitted_line, int index)
{
	while (splitted_line[index])
	{
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
			splitted_line[index]);
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "parsing_echo.c/L84"), NULL);
		if (splitted_line[index + 1] != NULL)
			info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
				" ");
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "parsing_echo.c/L89"), NULL);
		index++;
	}
	return (info_list);
}

t_lexer	*special_case_echo(t_lexer *info_list, char **splitted_line)
{
	int	index;

	index = 1;
	info_list->content = allocate_2d_arr(ft_strlen(splitted_line[0]) + 1, \
		info_list);
	if (!info_list->content)
		return (error_lex(info_list, 3, "parsing_echo.c/L103"), NULL);
	ft_strcpy(info_list->content[0], splitted_line[0]);
	if (splitted_line[index])
	{
		info_list->content[1] = ft_calloc(1, sizeof(char));
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "parsing_echo.c/L110"), NULL);
	}
	info_list = spca_echo_intolist(info_list, splitted_line, index);
	info_list = default_echo_data(info_list, splitted_line);
	info_list->next = NULL;
	free_double_array(splitted_line);
	return (info_list);
}
