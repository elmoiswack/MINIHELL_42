#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*intolist_commands(t_lexer *info_list, \
	char **splitted_line, int *enum_array)
{
	info_list->content = splitted_line;
	info_list->path = get_path_of_command(info_list->content[0], \
		info_list->env_copy);
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->next = NULL;
	info_list->check_free = 1;
	free(enum_array);
	return (info_list);
}
