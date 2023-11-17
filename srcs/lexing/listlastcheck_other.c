/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listlastcheck_other.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:38:54 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/17 13:43:35 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*listlastcheck_path(t_lexer *info_list)
{
	t_lexer	*head;

	head = info_list;
	while (info_list)
	{
		if (info_list->content && !info_list->path)
			info_list->path = \
				get_path_of_command(info_list->content[0], info_list->env_copy);
		info_list = info_list->next;
	}
	return (head);
}

t_lexer	*replacing_content_loop(t_lexer *info_list, char **array, int i, int j)
{
	while (array[i])
	{
		info_list->content[j] = ft_calloc(1, sizeof(char));
		if (!info_list->content[j])
			return (error_lex(info_list, 3, "listlastcheck_other.c/L26"), NULL);
		info_list->content[j] = \
			ft_strjoin_and_free(info_list->content[j], array[i]);
		if (!info_list->content[j])
			return (error_lex(info_list, 3, "listlastcheck_other.c/L29"), NULL);
		i++;
		j++;
	}
	info_list->content[j] = NULL;
	return (info_list);
}

t_lexer	*replacing_content(t_lexer *info_list, char **array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 1;
	temp = ft_strdup(info_list->content[0]);
	free_double_array(info_list->content);
	info_list->content = ft_calloc(get_max_array(array) + 2, sizeof(char *));
	if (!info_list->content)
		return (error_lex(info_list, 3, "listlastcheck_other.c/L43"), NULL);
	info_list->content[0] = ft_strdup(temp);
	if (!info_list->content[0])
		return (error_lex(info_list, 3, "listlastcheck_other.c/L43"), NULL);
	free(temp);
	info_list = replacing_content_loop(info_list, array, i, j);
	return (info_list);
}

t_lexer	*check_very_special(t_lexer *info_list, int i)
{
	t_lexer	*head;
	char	**random;

	head = info_list;
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "chmod", ft_strlen("chmod")) == 0)
			break ;
		if (ft_strncmp(info_list->content[0], "expr", ft_strlen("expr")) == 0)
			break ;
		info_list = info_list->next;
	}
	if (!info_list)
		return (head);
	while (info_list->content[i])
		i++;
	if (i >= 3)
		return (head);
	random = ft_split(info_list->content[1], ' ');
	if (!random)
		return (error_lex(info_list, 3, "listlastcheck_other.c/L61"), NULL);
	info_list = replacing_content(info_list, random);
	free_double_array(random);
	return (head);
}

t_lexer	*other_list_checks(t_lexer *info_list)
{
	t_lexer	*head;

	head = info_list;
	head = listlastcheck_path(head);
	while (info_list)
	{
		if (info_list->content)
		{
			head = check_very_special(head, 0);
			break ;
		}
		info_list = info_list->next;
	}
	return (head);
}
