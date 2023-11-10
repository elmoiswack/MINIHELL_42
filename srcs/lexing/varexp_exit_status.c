/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:51:03 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/10 13:54:15 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*replace_and_cat_line(char *new_var, \
	char *word_var, int index, t_lexer *info_list)
{
	int		temp;
	char	*status;

	index += 2;
	temp = ft_strlen(word_var) - index;
	status = ft_substr(word_var, index, temp);
	if (!status)
	{
		free(new_var);
		return (error_lex(info_list, 3, "varexp_utils.c/L114"), NULL);
	}
	new_var = ft_strjoin_and_free(new_var, status);
	return (new_var);
}

char	*expand_exit_status(char *word_var, t_lexer *info_list)
{
	char	*new_var;
	char	*status;
	int		index;

	index = 0;
	while (word_var[index] && word_var[index] != '$')
		index++;
	new_var = ft_substr(word_var, 0, index);
	if (!new_var)
		return (error_lex(info_list, 3, "varexp_utils.c/L101"), NULL);
	status = ft_itoa(info_list->exit_status);
	if (!status)
	{
		free(new_var);
		return (error_lex(info_list, 3, "varexp_utils.c/L104"), NULL);
	}
	new_var = ft_strjoin_and_free(new_var, status);
	free(status);
	if (!new_var)
		return (error_lex(info_list, 3, "varexp_utils.c/L110"), NULL);
	new_var = replace_and_cat_line(new_var, word_var, index, info_list);
	free(status);
	free(word_var);
	return (new_var);
}
