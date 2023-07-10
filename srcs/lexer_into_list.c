#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

t_lexer	*one_word_lexer(t_lexer *info_list, char **splitted_line)
{
	info_list->content = splitted_line;
	if (!info_list->content)
		return (NULL);
	info_list->path = get_path_of_command(info_list->content[0]);
	info_list->input = NONE;
	info_list->output = NONE;
	info_list->next = NULL;
	return (info_list);
}

t_lexer	*two_word_lexer(t_lexer *info_list, char **splitted_line)
{
	info_list->content = splitted_line;
	if (!info_list->content)
		return (NULL);
	info_list->path = get_path_of_command(info_list->content[0]);
	info_list->input = NONE;
	info_list->output = NONE;
	info_list->next = NULL;
	return (info_list);
}

t_lexer	*into_linklist(t_lexer *info_list, char *word_var, int enum_var)
{
	if (enum_var == COMMAND)
	{
		info_list->content = allocate_2d_arr(ft_strlen(word_var) + 1);
		if (!info_list->content)
			return (NULL);
		ft_strcpy(info_list->content[0], word_var);
		info_list->path = get_path_of_command(info_list->content[0]);
	}
	if (enum_var == FLAG)
	{
		info_list->content[1] = ft_calloc(ft_strlen(word_var) + 1, sizeof(char));
		if (!info_list->content[1])
			return (NULL);
		ft_strcpy(info_list->content[1], word_var);
	}
	if (enum_var == INFILE || enum_var == OUTFILE)
	{
		info_list->file = ft_calloc(ft_strlen(word_var) + 1, sizeof(char));
		if (!info_list->file)
			return (NULL);
		ft_strcpy(info_list->file, word_var);
	}
	if (enum_var == DELIMITER)
	{
		info_list->delim = ft_calloc(ft_strlen(word_var) + 1, sizeof(char));
		if (!info_list->delim)
			return (NULL);
		ft_strcpy(info_list->delim, word_var);
	}
	return (info_list);
}
