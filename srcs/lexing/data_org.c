#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*data_org_command(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	int	check;

	info_list = into_linklist(info_list, splitted_line[index], \
		enum_array[index]);
	if (!info_list)
		return (NULL);
	index++;
	check = check_for_flags(splitted_line, enum_array, index);
	if (check > 0)
		info_list = into_linklist(info_list, splitted_line[check], \
			enum_array[check]);
	return (info_list);
}

t_lexer	*data_org_pipe(t_lexer *info_list)
{
	if (info_list->input != INFILE && info_list->input != PIPE_READ)
		info_list->input = STDIN_IN;
	info_list->output = PIPE_WRITE;
	info_list = create_new_node(info_list);
	info_list->input = PIPE_READ;
	info_list->output = STDOUT_OUT;
	return (info_list);
}

t_lexer	*data_org_file(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	info_list = into_linklist(info_list, splitted_line[index], \
		enum_array[index]);
	if (!info_list)
		return (NULL);
	if (enum_array[index] == INFILE)
		info_list->input = INFILE;
	if (enum_array[index] == OUTFILE)
		info_list->output = OUTFILE;
	return (info_list);
}

t_lexer	*data_org_delim(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	if (splitted_line[index + 1])
		info_list = into_linklist(info_list, splitted_line[index + 1], \
			enum_array[index]);
	if (!info_list)
		return (NULL);
	return (info_list);
}

t_lexer	*organizing_data(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	t_lexer	*head;

	head = info_list;
	while (splitted_line[index])
	{
		if (enum_array[index] == COMMAND)
		{
			info_list = data_org_command(info_list, splitted_line, \
				enum_array, index);
			index++;
		}
		if (enum_array[index] == PIPE)
			info_list = data_org_pipe(info_list);
		if (enum_array[index] == INFILE || enum_array[index] == OUTFILE)
			info_list = data_org_file(info_list, splitted_line, \
				enum_array, index);
		if (enum_array[index] == DELIMITER)
		{
			info_list = data_org_delim(info_list, splitted_line, \
				enum_array, index);
			index++;
		}
		if (enum_array[index] == APPENDER)
		{
			if (splitted_line[index + 1])
			{
				index++;
				info_list->file = ft_calloc(ft_strlen(splitted_line[index]) + 1, \
					sizeof(char));
				if (!info_list->file)
					return (set_error_lex(info_list, 3, "data_org.c/L89"), NULL);
				ft_strcpy(info_list->file, splitted_line[index]);
				info_list->output = APPEND;
			}
		}
		if (!info_list)
			return (NULL);
		if (splitted_line[index] != NULL)
			index++;
	}
	info_list->next = NULL;
	return (head);
}
