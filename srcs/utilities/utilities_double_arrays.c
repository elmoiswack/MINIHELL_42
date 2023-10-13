#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	print_double_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
	{
		// if (arr[i])
		// 	ft_printf("%s\n", arr[i]);
		if (arr[i])
		{
			ft_putstr_fd(arr[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}

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
		copy[i] = ft_strdup(array[i]);
		i++;
	}
	return (copy);
}

char	**append_to_double_array(char **src, char *str)
{
	char	**new;
	int		n_of_arr;
	int		i;

	n_of_arr = 0;
	i = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 2);
	while (i < n_of_arr)
	{
		new[i] = ft_strdup(src[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	free_double_array(src);
	return (new);
}

char	**replace_str_in_array(char **src, char *str, int index)
{
	char	**new;
	int		n_of_arr;
	int		i;

	n_of_arr = 0;
	i = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	while (i < n_of_arr)
	{
		if (i == index)
			new[i] = ft_strdup(str);
		else
			new[i] = ft_strdup(src[i]);
		i++;
	}
	return (free_double_array(src), new);
}

char	**remove_str_from_array(char **src, int index)
{
	char	**new;
	int		n_of_arr;
	int		i;
	int		j;

	n_of_arr = 0;
	i = 0;
	j = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	if (!new)
		return (NULL);
	while (i < (n_of_arr - 1) && src[j])
	{
		if (j == index)
			j++;
		if (j > n_of_arr)
			new[i] = ft_strdup(src[n_of_arr]);
		else
			new[i] = ft_strdup(src[j]);
		i++;
		j++;
	}
	return (free_double_array(src), new);
}
