#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	free_double_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_lexing_struct(t_lexer *list)
{
	t_lexer *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

void	free_lexing_content_struct(t_lexer *list)
{
	while (list)
	{
		if (list->content)
			free_double_array(list->content);
		if (list->path)
			free(list->path);
		if (list->file)
			free(list->file);
		if (list->delim)
			free_double_array(list->delim);
		list = list->next;
	}
}