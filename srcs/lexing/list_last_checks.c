/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_last_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:57 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/01 20:50:02 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*remove_single_quotes(char *new, int *i_new, char *word_var, int *index)
{
	int	new_i;
	int	word_i;

	new_i = *i_new;
	word_i = *index;
	word_i++;
	while (word_var[word_i] && word_var[word_i] != '\'')
	{
		new[new_i] = word_var[word_i];
		new_i++;
		word_i++;
	}
	*index = word_i + 1;
	*i_new = new_i;
	return (new);
}

char	*remove_double_quotes(char *new, int *i_new, char *word_var, int *index)
{
	int	new_i;
	int	word_i;

	new_i = *i_new;
	word_i = *index;
	word_i++;
	while (word_var[word_i] && word_var[word_i] != '"')
	{
		new[new_i] = word_var[word_i];
		new_i++;
		word_i++;
	}
	*index = word_i + 1;
	*i_new = new_i;
	return (new);
}

char	*remove_quotes_loop(char *word_var)
{
	char	*new;
	int		i_new;
	int		index;

	new = ft_calloc(ft_strlen(word_var), sizeof(char));
	if (!new)
		return (NULL);
	index = 0;
	i_new = 0;
	while (word_var[index])
	{
		if (word_var[index] == '\'')
			new = remove_single_quotes(new, &i_new, word_var, &index);
		else if (word_var[index] == '"')
			new = remove_double_quotes(new, &i_new, word_var, &index);
		else
		{
			new[i_new] = word_var[index];
			i_new++;
			index++;
		}
	}
	free(word_var);
	return (new);
}

t_lexer	*check_quotes_list(t_lexer *info_list)
{
	t_lexer	*head;
	int		index;

	index = 0;
	head = info_list;
	while (info_list)
	{
		if (info_list->content)
		{
			while (info_list->content[index])
			{
				if (check_for_quotes(info_list->content[index]) == 1)
				{
					info_list->content[index] = \
						remove_quotes_loop(info_list->content[index]);
					if (!info_list->content[index])
						return (error_lex(info_list, 3, \
							"list_last_check.c/L35"), NULL);
				}
				index++;
			}
		}
		info_list = info_list->next;
	}
	return (head);
}
