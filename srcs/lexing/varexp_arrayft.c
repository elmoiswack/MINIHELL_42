#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**fill_array_env(char *line, int ammount_env, \
	char **env_temp, int index)
{
	int	index_temp;
	int	end;

	end = 0;
	index_temp = 0;
	while (ammount_env > 0)
	{
		if (line[index] == '$')
		{
			end = get_env_end(line, index + 1);
			env_temp[index_temp] = get_variable(line, index, end);
			if (!env_temp[index_temp])
			{
				free_double_array(env_temp);
				return (NULL);
			}
			ammount_env--;
			index += (end - index) - 1;
			index_temp++;
		}
		index++;
	}
	env_temp[index_temp] = NULL;
	return (env_temp);
}

char	*expand_variable(char *line, char **env_cpy)
{
	char	*temp;
	char	*env_temp;

	temp = remove_dollar_sign(line);
	free(line);
	env_temp = ft_getenv(temp, env_cpy);
	free(temp);
	if (!env_temp)
		return (NULL);
	temp = ft_calloc(ft_strlen(env_temp) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_strcpy(temp, env_temp);
	free(env_temp);
	return (temp);
}

char	**expand_env_variables(char **env_temp, char **env_cpy)
{
	int		index;

	index = 0;
	while (env_temp[index])
	{
		env_temp[index] = expand_variable(env_temp[index], env_cpy);
		if (!env_temp[index])
		{
			free(env_temp[index]);
			env_temp[index] = ft_calloc(2, sizeof(char));
			if (!env_temp[index])
				return (free_double_array(env_temp), NULL);
		}
		index++;
	}
	return (env_temp);
}

char	*remove_quotes_string_env(char **splitted_line, int index)
{
	char	*new_line;
	int		index_l;
	int		index_x;

	index_l = 0;
	index_x = 0;
	new_line = ft_calloc(ft_strlen(splitted_line[index]) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] != '"')
		{
			new_line[index_l] = splitted_line[index][index_x];
			index_l++;
		}
		index_x++;
	}
	free(splitted_line[index]);
	return (new_line);
}

char	**check_quotes_env(char **splitted_line)
{
	int	index;
	int	index_x;

	index = 0;
	while (splitted_line[index])
	{
		index_x = 0;
		while (splitted_line[index][index_x])
		{
			if (splitted_line[index][index_x] == '"')
			{
				splitted_line[index] = remove_quotes_string_env(splitted_line, \
					index);
				break ;
			}
			index_x++;
		}
		index++;
	}
	return (splitted_line);
}
