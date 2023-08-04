#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_env_in_string(char **splitted_line, int index)
{
	int	index_x;

	index_x = 0;
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == '$' \
			&& ft_isalpha(splitted_line[index][index_x + 1]) == 1)
			return (1);
		index_x++;
	}
	return (-1);
}

char	**fill_2d_array_env(char **splitted_line, int index, char **temp)
{
	int	index_x;
	int	index_t;
	int	index_tx;
	int	end;

	index_x = 0;
	index_t = 0;
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == '$')
		{
			index_tx = 0;
			end = index_x + 1;
			while (splitted_line[index][end] && splitted_line[index][end] != '$')
				end++;
			temp[index_t] = ft_calloc(end - index_x + 2, sizeof(char));
			if (!temp[index_t])
				return (NULL);
			while (index_x < end)
			{
				temp[index_t][index_tx] = splitted_line[index][index_x];
				index_tx++;
				index_x++;
			}
		}
		if (splitted_line[index][index_x] != '\0' && splitted_line[index][index_x] != '$')
			index_x++;
		index_t++;
	}
	return (temp);
}

char	**one_line_multenv(char **splitted_line, int index)
{
	char	**temp;
	char	*temp_line;
	int		index_te;

	index_te = 0;
	temp = ft_calloc(how_many_env(splitted_line, index) + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	temp = fill_2d_array_env(splitted_line, index, temp);
	if (!temp)
		return (NULL);
	temp_line = ft_calloc(1, sizeof(char));
	if (!temp_line)
		return (NULL);
	while (temp[index_te])
	{
		temp = one_case(temp, index_te);
		if (!temp)
			return (NULL);
		temp_line = ft_strjoin_and_free(temp_line, temp[index_te]);
		if (!temp_line)
			return (NULL);
		index_te++;
	}
	free_double_array(temp);
	free(splitted_line[index]);
	splitted_line[index] = temp_line;
	return (splitted_line);
}

char	*fill_temp_line(char **splitted_line, int index, char **temp, char *temp_line)
{
	int	index_tmp;
	int	len;

	index_tmp = 0;
	len = 0;
	while (temp[index_tmp])
	{
		len += ft_strlen(temp[index_tmp]);
		if (splitted_line[index][len + 1] == ' ')
			len++;
		if (temp[index_tmp][0] == '$')
		{
			temp = one_case(temp, index_tmp);
			if (!temp)
				return (NULL);
		}
		temp_line = ft_strjoin_and_free(temp_line, temp[index_tmp]);
		if (splitted_line[index][len] == ' ')
			temp_line = ft_strjoin_and_free(temp_line, " ");
		if (!temp_line)
			return (NULL);
		index_tmp++;
	}
	return (temp_line);
}

char	**mult_line_multenv(char **splitted_line, int index)
{
	char	**temp;
	int		index_tmp;
	char	*temp_line;

	index_tmp = 0;
	temp = ft_split(splitted_line[index], ' ');
	if (!temp)
		return (NULL);
	while (temp[index_tmp])
	{
		if (check_multiple_env(temp, index_tmp) == 1)
			temp = one_line_multenv(temp, index_tmp);
		index_tmp++;
	}
	temp_line = ft_calloc(1, sizeof(char));
	if (!temp_line)
		return (NULL);
	temp_line = fill_temp_line(splitted_line, index, temp, temp_line);
	if (!temp_line)
		return (NULL);
	free_double_array(temp);
	free(splitted_line[index]);
	splitted_line[index] = temp_line;
	return (splitted_line);
}