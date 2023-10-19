#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	free_double_array(char **array)
{
	int	i;

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
	t_lexer	*temp;

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
		if (list->infile)
			free_double_array(list->infile);
		if (list->outfile)
			free_double_array(list->outfile);
		if (list->delim)
			free_double_array(list->delim);
		list = list->next;
	}
}

void	error_lex(t_lexer *info_list, int error_code, const char *str)
{
	info_list->error_code = error_code;
	info_list->error_str = str;
	error_lexing_message(info_list);
	free_lexing_content_struct(info_list);
	free_lexing_struct(info_list);
}
