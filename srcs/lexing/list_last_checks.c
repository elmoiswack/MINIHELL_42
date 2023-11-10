/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_last_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:57 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/09 18:32:32 by dantehussai      ###   ########.fr       */
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
	if (word_var[word_i] != '\0')
		*index = word_i + 1;
	else
		*index = word_i;
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
	if (word_var[word_i] != '\0')
		*index = word_i + 1;
	else
		*index = word_i;
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

char	**quotes_loop(char **array, t_lexer *info_list)
{
	int	index;

	index = 0;
	while (array[index])
	{
		if (check_for_quotes(array[index]) == 1)
		{
			array[index] = \
				remove_quotes_loop(array[index]);
			if (!array[index])
				return (error_lex(info_list, 3, \
					"list_last_check.c/L94"), NULL);
		}
		index++;
	}
	return (array);
}

t_lexer *check_chmod(t_lexer *info_list)
{
	t_lexer *head;
	char	**temp;
	char	**random;
	
	head = info_list;
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "chmod", ft_strlen("chmod")) == 0)
			break ;
		info_list = info_list->next;
	}
	if (!info_list)
		return (head);
	int i = 0;
	while (info_list->content[i])
		i++;
	if (i == 3)
		return (head);
	temp = ft_copy_double_array(info_list->content);
	random = ft_split(temp[1], ' ');
	free_double_array(info_list->content);
	info_list->content = allocate_2d_arr(ft_strlen("chmod"), info_list);
	info_list->content[0] = ft_strjoin_and_free(info_list->content[0], "chmod");
	i = 0;
	int j = 1;
	while (random[i])
	{
		info_list->content[j] = ft_calloc(1, sizeof(char));
		info_list->content[j] = ft_strjoin_and_free(info_list->content[j], random[i]);
		i++;
		j++;
	}
	info_list->content[j] = NULL;
	free_double_array(temp);
	free_double_array(random);
	return (head);
}

t_lexer	*check_quotes_list(t_lexer *l, t_lexer *head)
{
	head = l;
	while (l)
	{
		if (l->content)
		{
			l->content = quotes_loop(l->content, l);
			if (!l->content)
				return (NULL);
		}
		if (l->outfile)
		{
			l->outfile = quotes_loop(l->outfile, l);
			if (!l->outfile)
				return (NULL);
		}
		if (l->infile)
		{
			l->infile = quotes_loop(l->infile, l);
			if (!l->infile)
				return (NULL);
		}
		l = l->next;
	}
	head = listlastcheck_path(head);
	head = check_chmod(head);
	return (head);
}
