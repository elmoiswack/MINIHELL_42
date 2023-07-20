#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_for_envvar(char **splitted_line, int *enum_array)
{
	int	index;

	index = 0;
	while (splitted_line[index])
	{
		if (enum_array[index] == ENV_VAR)
			return (1);
		index++;
	}
	return (-1);
}

char	*trim_envvar(char *line)
{
	char	*temp;
	int		index;
	int		begin_word;
	int		index_temp;

	index = 0;
	index_temp = 0;
	begin_word = 0;
	while (line[begin_word] && line[begin_word] != '"')
		begin_word++;
	if (line[begin_word] == '\0')
		return (NULL);
	begin_word++;
	index = begin_word;
	while (line[index] && line[index] != '"')
		index++;
	if (line[index] == '\0')
		return (NULL);
	temp = ft_calloc((index - begin_word) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (begin_word < index)
	{
		temp[index_temp] = line[begin_word];
		index_temp++;
		begin_word++;
	}
	free(line);
	return (temp);
}

char	**new_2d_array(char **splitted_line)
{
	char	**temp;
	int		max;
	int		index;
	int		index_temp;

	index = 1;
	max = 0;
	index_temp = 0;
	while (splitted_line[max])
		max++;
	temp = ft_calloc(max, sizeof(char *));
	if (!temp)
		return (NULL);
	while (index < max)
	{
		temp[index_temp] = ft_calloc(ft_strlen(splitted_line[index]) + 1, sizeof(char));
		if (!temp[index_temp])
			return (NULL);
		ft_strcpy(temp[index_temp], splitted_line[index]);
		index_temp++;
		index++;
	}
	free_2d_array(splitted_line);
	temp[index_temp] = NULL;
	return (temp);
}

char	**edit_arr_env(char **splitted_line, int *enum_array)
{
	int	index;

	index = 0;
	while (enum_array[index] != ENV_VAR)
		index++;
	splitted_line[0] = trim_envvar(splitted_line[0]);
	if (!splitted_line[0])
		return (NULL);
	free(splitted_line[index]);
	splitted_line[index] = ft_calloc(ft_strlen(splitted_line[0]) + 1, sizeof(char));
	if (!splitted_line[index])
		return (NULL);
	ft_strcpy(splitted_line[index], splitted_line[0]);
	splitted_line = new_2d_array(splitted_line);
	return (splitted_line);
}
//kdasdas
