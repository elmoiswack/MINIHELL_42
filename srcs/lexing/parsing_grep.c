#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_for_grep(t_lexer *info_list)
{
	if (!info_list->content)
		return (-1);
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "grep", ft_strlen("grep")) == 0)
			return (1);
		info_list = info_list->next;
	}
	return (-1);
}

char	*rm_guotes_loop(t_lexer *info_list, char *temp)
{
	int	index_c;
	int	index_te;

	index_c = 0;
	index_te = 0;
	while (info_list->content[1][index_c])
	{
		if (info_list->content[1][index_c] != 39)
		{
			temp[index_te] = info_list->content[1][index_c];
			index_te++;
		}
		index_c++;
	}
	return (temp);
}

t_lexer	*rm_quotes_grep(t_lexer *info_list)
{
	char	*temp;
	t_lexer	*head;

	head = info_list;
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "grep", ft_strlen("grep")) == 0 \
			&& info_list->content[1][0] == 39)
			break ;
		info_list = info_list->next;
	}
	temp = ft_calloc(ft_strlen(info_list->content[1]) + 1, sizeof(char));
	if (!temp)
		return (set_error_lex(info_list, 3, "parsing_grep.c/L49"), NULL);
	temp = rm_guotes_loop(info_list, temp);
	free(info_list->content[1]);
	info_list->content[1] = temp;
	return (head);
}

t_lexer	*add_flag_grep(t_lexer *info_list, char **splitted_line)
{
	t_lexer	*head;
	int		index;

	index = 0;
	head = info_list;
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "grep", ft_strlen("grep")) == 0)
			break ;
		info_list = info_list->next;
	}
	while (splitted_line[index])
	{
		if (ft_strncmp(splitted_line[index], "grep", ft_strlen("grep")) == 0)
			break ;
		index++;
	}
	index++;
	info_list->content[1] = ft_calloc(ft_strlen(splitted_line[index]) + 1, \
		sizeof(char));
	if (!info_list->content[1])
		return (set_error_lex(info_list, 3, "parsing_grep.c/L78"), NULL);
	ft_strcpy(info_list->content[1], splitted_line[index]);
	return (head);
}

t_lexer	*grep_parser(t_lexer *info_list, char **splitted_line)
{
	t_lexer	*head;

	head = info_list;
	while (info_list)
	{
		if (ft_strncmp(info_list->content[0], "grep", ft_strlen("grep")) == 0)
			break ;
		info_list = info_list->next;
	}
	if (!info_list->content[1])
	{
		info_list = add_flag_grep(info_list, splitted_line);
		if (!info_list)
			return (NULL);
	}
	if (info_list->content[1] && info_list->content[1][0] == 39)
	{
		info_list = rm_quotes_grep(info_list);
		if (!info_list)
			return (NULL);
		return (head);
	}
	return (head);
}
