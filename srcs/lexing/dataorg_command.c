/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataorg_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:26:43 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/26 14:31:59 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*data_org_command(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	int	check;

	info_list = into_linklist(info_list, splitted_line[index], \
		enum_array[index]);
	if (!info_list)
		return (NULL);
	index++;
	check = check_for_flags(splitted_line, enum_array, index);
	if (check > 0)
	{
		if (!info_list->content[1])
			info_list->content[1] = ft_calloc(1, sizeof(char));
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "into_list_cases.c/L19"), NULL);
		while (enum_array[index] != FLAG)
			index++;
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
			splitted_line[index]);
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "into_list_cases.c/L82"), NULL);
		info_list = into_linklist_flag(info_list, splitted_line, \
			enum_array, index + 1);
	}
	return (info_list);
}

char	*rm_dash_flag(char *word_var)
{
	int		index_old;
	int		index_new;
	char	*new_line;

	index_old = 0;
	index_new = 0;
	new_line = ft_calloc(ft_strlen(word_var), sizeof(char));
	if (!new_line)
		return (NULL);
	while (word_var[index_old])
	{
		if (word_var[index_old] != '-')
		{
			new_line[index_new] = word_var[index_old];
			index_new++;
		}
		index_old++;
	}
	free(word_var);
	return (new_line);
}

t_lexer	*into_linklist_flag(t_lexer *list, \
	char **split_l, int *enum_array, int i)
{
	while (split_l[i])
	{
		if (enum_array[i] == COMMAND || enum_array[i] == PIPE)
			break ;
		if (enum_array[i] == FLAG)
		{
			if (split_l[i][0] == '-')
			{
				split_l[i] = rm_dash_flag(split_l[i]);
				if (!split_l[i])
					return (error_lex(list, 3, "dataorg_command.c/L94"), NULL);
			}
			else
				list->content[1] = ft_strjoin_and_free(list->content[1], " ");
			if (!list->content[1])
				return (error_lex(list, 3, \
					"into_list_cases.c/L29"), NULL);
			list->content[1] = \
				ft_strjoin_and_free(list->content[1], split_l[i]);
			if (!list->content[1])
				return (error_lex(list, 3, "into_list_cases.c/L82"), NULL);
		}
		i++;
	}
	return (list);
}
