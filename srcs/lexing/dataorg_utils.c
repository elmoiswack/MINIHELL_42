#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_lexer	*create_new_node(t_lexer *info_lexer)
{
	info_lexer->next = ft_calloc(1, sizeof(t_lexer));
	if (!info_lexer->next)
		return (error_lex(info_lexer, 3, "dataorg_utils.c/L21"), NULL);
	info_lexer = info_lexer->next;
	info_lexer->next = NULL;
	return (info_lexer);
}

char	**allocate_2d_arr(int size, t_lexer *info_list)
{
	char	**arr;

	arr = ft_calloc(4, sizeof(char *));
	if (!arr)
		return (error_lex(info_list, 3, "dataorg_utils.c/L33"), NULL);
	arr[0] = ft_calloc(size, sizeof(char));
	if (!arr[0])
		return (error_lex(info_list, 3, "dataorg_utils.c/L36"), NULL);
	arr[1] = NULL;
	arr[2] = NULL;
	arr[3] = NULL;
	return (arr);
}

int	check_for_outfile(char **splitted_line, int *enum_array, int index)
{
	while (splitted_line[index])
	{
		if (enum_array[index] == REDIRECT_OUT)
			return (1);
		index++;
	}
	return (-1);
}

int	check_for_flags(char **splitted_line, int *enum_arr, int index)
{
	int	count;

	count = 0;
	while (splitted_line[index])
	{
		if (enum_arr[index] == COMMAND)
			return (count);
		if (enum_arr[index] == FLAG)
			count++;
		index++;
	}
	return (count);
}
