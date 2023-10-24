/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_delim_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:17 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/24 14:10:04 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	get_number_delim(int *enum_array)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (enum_array[index])
	{
		if (enum_array[index] == DELIMITER)
			count++;
		index++;
	}
	return (count);
}

t_lexer	*alloc_infile(t_lexer *info_list, int *enum_array)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (enum_array[index])
	{
		if (enum_array[index] == INFILE)
			count++;
		index++;
	}
	if (count == 0)
		return (info_list);
	info_list->infile = ft_calloc(count + 1, sizeof(char *));
	if (!info_list->infile)
		return (error_lex(info_list, 2, "dataorg_utils.c/L49"), NULL);
	return (info_list);
}

t_lexer	*allocate_files(t_lexer *info_list, int *enum_array)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	info_list = alloc_infile(info_list, enum_array);
	if (!info_list)
		return (NULL);
	while (enum_array[index])
	{
		if (enum_array[index] == OUTFILE || enum_array[index] == APPENDER)
			count++;
		index++;
	}
	if (count == 0)
		return (info_list);
	info_list->outfile = ft_calloc(count + 1, sizeof(char *));
	if (!info_list->outfile)
		return (error_lex(info_list, 2, "dataorg_utils.c/L73"), NULL);
	info_list->index_inf = 0;
	info_list->index_outf = 0;
	return (info_list);
}
