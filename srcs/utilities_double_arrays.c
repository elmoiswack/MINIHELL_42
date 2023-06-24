#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	free_double_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_double_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
	{
		if (arr[i])
			ft_printf("%s\n", arr[i]);
	}
}

char	**copy_double_array(char **array)
{
	char	**copy;
	int		n_of_arr;
	int		len;
	int		i;

	n_of_arr = 0;
	len = 0;
	i = 0;
	while (array[n_of_arr])
		n_of_arr++;

	copy = ft_calloc(sizeof(char *), n_of_arr + 1);
	while (i < n_of_arr)
	{
		len = ft_strlen(array[i]);
		copy[i] = malloc(sizeof(char) * len + 1);
		ft_strlcpy(copy[i], array[i], len);
		i++;
	}
	// print_double_array(copy);
	return (copy);
}
