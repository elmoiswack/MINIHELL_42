#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*copy_without_doubles(char *cont_line, char *temp)
{
	int	index;
	int	index_tmp;

	index = 0;
	index_tmp = 0;
	while (cont_line[index])
	{
		if (cont_line[index] != '"')
		{
			temp[index_tmp] = cont_line[index];
			index_tmp++;
		}
		index++;
	}
	return (temp);
}

char	**remove_doubles(char **content)
{
	int	index;
	char *temp;

	index = 0;
	while (content[index])
	{
		temp = ft_calloc(ft_strlen(content[index]) + 1, sizeof(char));
		if (!temp)
		{
			free_double_array(content);
			return (NULL);
		}
		temp = copy_without_doubles(content[index], temp);
		free(content[index]);
		content[index] = temp;
		index++;
	}
	return (content);
}

t_lexer	*check_quotes_list(t_lexer *info_list)
{
	t_lexer *head;

	head = info_list;
	while (info_list)
	{
		if (info_list->content)
		{
			info_list->content = remove_doubles(info_list->content);
			if (!info_list->content)
				return (error_lex(info_list, 3, "list_checks.c/L38"), NULL);
		}
		info_list = info_list->next;
	}
	return (head);
}