#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

t_lexer	*one_two_word_lexer(t_lexer *info_list, char **splitted_line)
{
	info_list->content = splitted_line;
	info_list->path = get_path_of_command(info_list->content[0], info_list->env_copy);
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->next = NULL;
	return (info_list);
}

t_lexer	*into_linklist_flag(t_lexer *info_list, char *word_var)
{
	info_list->content[1] = ft_calloc(ft_strlen(word_var) + 1, \
		sizeof(char));
	if (!info_list->content[1])
		return (error_lex(info_list, 3, "into_list.c/L17"), NULL);
	ft_strcpy(info_list->content[1], word_var);
	return (info_list);
}

t_lexer	*into_linklist_command(t_lexer *info_list, char *word_var)
{
	info_list->content = allocate_2d_arr(ft_strlen(word_var) + 1, \
		info_list);
	if (!info_list->content)
		return (error_lex(info_list, 3, "into_list.c/L27"), NULL);
	ft_strcpy(info_list->content[0], word_var);
	info_list->path = get_path_of_command(info_list->content[0], info_list->env_copy);
	return (info_list);
}

t_lexer	*into_linklist_delim(t_lexer *info_list, char *word_var)
{
	int	in_delim;

	in_delim = info_list->index_delim;
	info_list->delim[in_delim] = ft_calloc(ft_strlen(word_var) + 1, \
		sizeof(char));
	if (!info_list->delim[in_delim])
		return (error_lex(info_list, 3, "into_list.c/L41"), NULL);
	ft_strcpy(info_list->delim[in_delim], word_var);
	info_list->index_delim += 1;
	return (info_list);
}

t_lexer	*into_linklist(t_lexer *info_list, char *word_var, int enum_var)
{
	if (enum_var == COMMAND)
	{
		info_list = into_linklist_command(info_list, word_var);
		if (!info_list)
			return (NULL);
	}
	if (enum_var == FLAG)
	{
		info_list = into_linklist_flag(info_list, word_var);
		if (!info_list)
			return (NULL);
	}
	if (enum_var == INFILE || enum_var == OUTFILE)
	{
		info_list->file = ft_calloc(ft_strlen(word_var) + 1, sizeof(char));
		if (!info_list->file)
			return (error_lex(info_list, 3, "into_list.c/L66"), NULL);
		ft_strcpy(info_list->file, word_var);
	}
	if (enum_var == DELIMITER)
		info_list = into_linklist_delim(info_list, word_var);
	return (info_list);
}
