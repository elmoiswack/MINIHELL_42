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
		len = ft_strlen(array[i]) + 1;
		copy[i] = malloc(sizeof(char) * len + 1);
		ft_strlcpy(copy[i], array[i], len);
		i++;
	}
	return (copy);
}

char	**append_to_double_array(char **src, char *str)
{
	char	**new;
	int		n_of_arr;
	int		len;
	int		i;

	n_of_arr = 0;
	len = 0;
	i = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 2);
	while (i < n_of_arr)
	{
		len = ft_strlen(src[i]) + 1;
		new[i] = malloc(sizeof(char) * len + 1);
		ft_strlcpy(new[i], src[i], len);
		i++;
	}
	len = ft_strlen(str) + 1;
	new[i] = malloc(sizeof(char) * len + 1);
	ft_strlcpy(new[i], str, len);
	free_double_array(src);
	return (new);
}

char	**replace_str_in_array(char **src, char *str, int index)
{
	char	**new;
	int		n_of_arr;
	int		len;
	int		i;

	n_of_arr = 0;
	len = 0;
	i = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	while (i < n_of_arr)
	{
		if (i == index)
		{
			len = ft_strlen(str) + 1;
			new[i] = malloc(sizeof(char) * len + 1);
			ft_strlcpy(new[i], str, len);
		}
		else
		{
			len = ft_strlen(src[i]);
			new[i] = malloc(sizeof(char) * len + 1);
			ft_strlcpy(new[i], src[i], len);
		}
		i++;
	}
	free_double_array(src);
	return (new);
}

char	**remove_str_from_array(char **src, int index)
{
	char	**new;
	int		n_of_arr;
	int		len;
	int		i;
	int		j;

	n_of_arr = 0;
	len = 0;
	i = 0;
	j = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	while (i < (n_of_arr - 1) && src[j])
	{
		if (j == index)
			j++;
		len = ft_strlen(src[j]) + 1;
		new[i] = malloc(sizeof(char) * len + 1);
		if (j > n_of_arr)
			ft_strlcpy(new[i], src[n_of_arr], len);
		else
			ft_strlcpy(new[i], src[j], len);
		i++;
		j++;
	}
	free_double_array(src);
	return (new);
}
