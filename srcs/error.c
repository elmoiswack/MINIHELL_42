#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	free_2d_array(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
	return ;
}
//kdasdas