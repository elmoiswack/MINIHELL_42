/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:31 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/26 14:02:02 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

t_lexer	*one_two_word_lexer(t_lexer *info_list, char **splitted_line)
{
	info_list->content = splitted_line;
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
		info_list = into_linklist_command(info_list, word_var);
	else if (enum_var == INFILE)
		info_list = into_linklist_infile(info_list, word_var);
	else if (enum_var == OUTFILE)
		info_list = into_linklist_outfile(info_list, word_var);
	else if (enum_var == DELIMITER)
		info_list = into_linklist_delim(info_list, word_var);
	return (info_list);
}
