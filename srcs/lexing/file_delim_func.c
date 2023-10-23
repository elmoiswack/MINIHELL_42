#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	get_number_delim(int *enum_array)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (enum_array[index])
	{
		if (enum_array[index] == DELIMITER)
			count++;
		index++;
	}
	return (count);
}

t_lexer	*alloc_infile(t_lexer *info_list, int *enum_array)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (enum_array[index])
	{
		if (enum_array[index] == INFILE)
			count++;
		index++;
	}
	if (count == 0)
		return (info_list);
	info_list->infile = ft_calloc(count + 1, sizeof(char *));
	if (!info_list->infile)
		return (error_lex(info_list, 2, "dataorg_utils.c/L70"), NULL);
	return (info_list);	
}

t_lexer	*allocate_files(t_lexer *info_list, int *enum_array)
{
	int	count;
	int	index;
	
	count = 0;
	index = 0;
	info_list = alloc_infile(info_list, enum_array);
	if (!info_list)
		return (NULL);
	while (enum_array[index])
	{
		if (enum_array[index] == OUTFILE)
			count++;
		index++;
	}
	if (count == 0)
		return (info_list);
	info_list->outfile = ft_calloc(count + 1, sizeof(char *));
	if (!info_list->outfile)
		return (error_lex(info_list, 2, "dataorg_utils.c/L70"), NULL);
	info_list->index_inf = 0;
	info_list->index_outf = 0;
	return (info_list);
}
