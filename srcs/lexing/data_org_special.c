#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

// t_lexer	*echo_with_meta(t_lexer *info_list, char **splitted_line, int *enum_array)
// {

// }

t_lexer	*special_case_echo(t_lexer *info_list, char **splitted_line, int *enum_array)
{
	int		index;
	
	// index = 0;
	// while (splitted_line[index])
	// {
	// 	if (is_metacharachter(splitted_line[index][0]) == 1)
	// 		return (echo_with_meta(info_list, splitted_line, enum_array));
	// 	index++;
	// }
	enum_array = 0;
	index = 1;
	info_list->content = allocate_2d_arr(ft_strlen(splitted_line[0]) + 1);
	ft_strcpy(info_list->content[0], splitted_line[0]);
	while (splitted_line[index])
	{
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], splitted_line[index]);
		if (splitted_line[index + 1] != NULL)
			info_list->content[1] = ft_strjoin_and_free(info_list->content[1], " ");
		index++;
	}
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->path = get_path_of_command(splitted_line[0]);
	info_list->next = NULL;
	free_2d_array(splitted_line);
	return (info_list);
}

// t_lexer	*special_case_cat(t_lexer *info_list, char **splitted_line, int *enum_array)
// {

// }