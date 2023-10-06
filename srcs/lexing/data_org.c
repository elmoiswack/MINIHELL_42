#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*organizing_data_checks(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	if (enum_array[index] == COMMAND)
	{
		info_list = data_org_command(info_list, splitted_line, \
			enum_array, index);
	}
	else if (enum_array[index] == PIPE)
		info_list = data_org_pipe(info_list);
	else if (enum_array[index] == INFILE || enum_array[index] == OUTFILE)
		info_list = data_org_file(info_list, splitted_line, \
			enum_array, index);
	else if (enum_array[index] == DELIMITER)
	{
		info_list = data_org_delim(info_list, splitted_line, \
			enum_array, index);
		index++;
	}
	else if (enum_array[index] == APPENDER)
	{
		info_list = data_org_appender(info_list, splitted_line, index);
	}
	return (info_list);
}

t_lexer	*organizing_data(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	t_lexer	*head;

	head = info_list;
	while (splitted_line[index])
	{
		info_list = organizing_data_checks(info_list, splitted_line, \
			enum_array, index);
		if (!info_list)
			return (NULL);
		if ((enum_array[index] == DELIMITER) || (enum_array[index] == APPENDER))
			index++;
		if (splitted_line[index] != NULL)
			index++;
	}
	info_list->next = NULL;
	return (head);
}
