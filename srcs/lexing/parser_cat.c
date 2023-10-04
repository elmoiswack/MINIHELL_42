#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_for_cat(t_lexer *info_list)
{
	if (!info_list->content)
		return (-1);
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "cat", ft_strlen("cat")) == 0)
			return (1);
		info_list = info_list->next;
	}
	return (-1);
}

t_lexer	*check_content(t_lexer *info_list, char **splitted_line, int index)
{
	if (!info_list->content[1])
	{
		info_list->content[1] = ft_calloc(ft_strlen(splitted_line[index]) + 1, \
			sizeof(char));
		if (!info_list->content[1])
			return (error_lex(info_list, 3, "parses_cat.c/L21"), NULL);
		ft_strcpy(info_list->content[1], splitted_line[index]);
	}
	return (info_list);
}

t_lexer	*cat_parser(t_lexer *info_list, char **splitted_line)
{
	int		index;
	t_lexer	*head;

	head = info_list;
	index = 0;
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "cat", ft_strlen("cat")) == 0)
			break ;
		info_list = info_list->next;
	}
	while (splitted_line[index])
	{
		if (ft_strncmp(splitted_line[index], "cat", ft_strlen("cat")) == 0)
			break ;
		index++;
	}
	if (splitted_line[index + 1] != NULL && \
		is_metacharachter(splitted_line[index + 1][0]) != 1)
	{
		info_list = check_content(info_list, splitted_line, index + 1);
		if (!info_list)
			return (NULL);
	}
	return (head);
}
