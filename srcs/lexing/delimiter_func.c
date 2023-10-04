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
