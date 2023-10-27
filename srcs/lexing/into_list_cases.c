/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_list_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:24 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/27 14:59:35 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

t_lexer	*into_linklist_command(t_lexer *info_list, char *word_var)
{
	if (!info_list->content)
	{
		info_list->content = allocate_2d_arr(ft_strlen(word_var) + 1, \
			info_list);
		if (!info_list->content)
			return (error_lex(info_list, 3, "into_list.c/L29"), NULL);
		ft_strcpy(info_list->content[0], word_var);
		info_list->path = get_path_of_command(info_list->content[0], \
			info_list->env_copy);
	}
	else
	{
		if (!info_list->content[1])
			info_list->content[1] = ft_calloc(1, sizeof(char));
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "into_list_cases.c/L32"), NULL);
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], " ");
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "into_list_cases.c/L32"), NULL);
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
			word_var);
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "into_list_cases.c/L32"), NULL);
	}
	return (info_list);
}

t_lexer	*into_linklist_delim(t_lexer *info_list, char *word_var)
{
	int	in_delim;

	in_delim = info_list->index_delim;
	info_list->delim[in_delim] = ft_calloc(ft_strlen(word_var) + 1, \
		sizeof(char));
	if (!info_list->delim[in_delim])
		return (error_lex(info_list, 3, "into_list_cases.c/L44"), NULL);
	ft_strcpy(info_list->delim[in_delim], word_var);
	info_list->index_delim += 1;
	return (info_list);
}

t_lexer	*into_linklist_infile(t_lexer *info_list, char *word_var)
{
	info_list->infile[info_list->index_inf] = \
		ft_calloc(ft_strlen(word_var) + 1, sizeof(char));
	if (!info_list->infile[info_list->index_inf])
		return (error_lex(info_list, 3, "into_list_cases.c/L55"), NULL);
	ft_strcpy(info_list->infile[info_list->index_inf], word_var);
	info_list->index_inf += 1;
	return (info_list);
}

t_lexer	*into_linklist_outfile(t_lexer *info_list, char *word_var)
{
	info_list->outfile[info_list->index_outf] = \
		ft_calloc(ft_strlen(word_var) + 1, sizeof(char));
	if (!info_list->outfile[info_list->index_outf])
		return (error_lex(info_list, 3, "into_list.c/L66"), NULL);
	ft_strcpy(info_list->outfile[info_list->index_outf], word_var);
	info_list->index_outf += 1;
	return (info_list);
}
