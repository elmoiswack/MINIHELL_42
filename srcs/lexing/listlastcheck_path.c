#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer *listlastcheck_path(t_lexer *info_list)
{
	t_lexer *head;
	
	head = info_list;
	while (info_list)
	{
		if (info_list->content && !info_list->path)
			info_list->path = get_path_of_command(info_list->content[0], info_list->env_copy);
		info_list = info_list->next;
	}
	return (head);
}