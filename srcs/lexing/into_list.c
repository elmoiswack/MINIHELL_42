/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:31 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/09 18:19:19 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

t_lexer	*one_two_word_lexer(t_lexer *info_list, char **splitted_line, int *enum_array)
{
	int i;

	i = 0;
	while (splitted_line[i])
	{
		if (is_metacharachter(splitted_line[i][0]) == 1)
			break ;
		i++;
	}
	if (splitted_line[i] != NULL && is_metacharachter(splitted_line[i][0]) == 1)
	{
		info_list = organizing_data(info_list, splitted_line, enum_array, 0);
		if (!info_list)
			return (NULL);
	}
	else
		info_list->content = splitted_line;
	if 	(info_list->content)
		info_list->path = get_path_of_command(info_list->content[0], \
			info_list->env_copy);
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->next = NULL;
	return (info_list);
}

t_lexer	*into_linklist(t_lexer *info_list, char *word_var, int enum_var)
{
	if (enum_var == COMMAND)
	{
		if (info_list->content && info_list->content[1] == NULL)
		{
			info_list->content[1] = ft_calloc(1, sizeof(char));
			if (!info_list->content[1])
				return (error_lex(info_list, 3, "into_list_cases.c/L32"), NULL);
		}
		info_list = into_linklist_command(info_list, word_var);
	}
	else if (enum_var == INFILE)
		info_list = into_linklist_infile(info_list, word_var);
	else if (enum_var == OUTFILE)
		info_list = into_linklist_outfile(info_list, word_var);
	else if (enum_var == DELIMITER)
		info_list = into_linklist_delim(info_list, word_var);
	return (info_list);
}
