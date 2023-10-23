/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intolist_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:34 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/23 15:39:35 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*intolist_commands(t_lexer *info_list, \
	char **splitted_line, int *enum_array)
{
	info_list->content = splitted_line;
	info_list->path = get_path_of_command(info_list->content[0], \
		info_list->env_copy);
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->next = NULL;
	info_list->check_free = 1;
	free(enum_array);
	return (info_list);
}
