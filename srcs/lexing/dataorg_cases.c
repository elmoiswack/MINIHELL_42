/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataorg_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:38:43 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/23 15:41:03 by dhussain         ###   ########.fr       */
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
		info_list = into_linklist(info_list, splitted_line[check], \
			enum_array[check]);
	return (info_list);
}

t_lexer	*data_org_pipe(t_lexer *info_list)
{
	char	**temp_env;

	temp_env = info_list->env_copy;
	if (info_list->input != INFILE && info_list->input != PIPE_READ)
		info_list->input = STDIN_IN;
	info_list->output = PIPE_WRITE;
	info_list = create_new_node(info_list);
	info_list->index_inf = 0;
	info_list->index_outf = 0;
	info_list->env_copy = temp_env;
	info_list->input = PIPE_READ;
	info_list->output = STDOUT_OUT;
	return (info_list);
}

t_lexer	*data_org_file(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	info_list = into_linklist(info_list, splitted_line[index], \
		enum_array[index]);
	if (!info_list)
		return (NULL);
	if (enum_array[index] == INFILE)
		info_list->input = INFILE;
	if (enum_array[index] == OUTFILE)
		info_list->output = OUTFILE;
	return (info_list);
}

t_lexer	*data_org_delim(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	int	ammount_words;

	if (!info_list->delim)
	{
		ammount_words = get_number_delim(enum_array);
		if (ammount_words > 0)
		{
			info_list->delim = ft_calloc(ammount_words + 1, sizeof(char *));
			if (!info_list->delim)
				return (NULL);
		}
	}
	if (splitted_line[index + 1])
		info_list = into_linklist(info_list, splitted_line[index + 1], \
			enum_array[index]);
	info_list->input = HEREDOC;
	return (info_list);
}

t_lexer	*data_org_appender(t_lexer *info_list, char **splitted_line, int index)
{
	if (splitted_line[index])
	{
		info_list->outfile[info_list->index_outf] = \
			ft_calloc(ft_strlen(splitted_line[index]) + 1, \
			sizeof(char));
		if (!info_list->outfile[info_list->index_outf])
			return (error_lex(info_list, 3, "dataorg_cases.c/L92"), \
				NULL);
		ft_strcpy(info_list->outfile[info_list->index_outf], \
			splitted_line[index]);
		info_list->output = APPEND;
	}
	return (info_list);
}
