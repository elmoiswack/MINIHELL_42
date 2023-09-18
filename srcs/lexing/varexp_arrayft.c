#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**fill_array_env(char *line, int ammount_env, char **env_temp)
{
	int	index;
	int	index_temp;
	int	end;

	index = 0;
	end = 0;
	index_temp = 0;
	while (ammount_env > 0)
	{
		if (line[index] == '$')
		{
			end = get_env_end(line, index + 1);
			env_temp[index_temp] = get_variable(line, index, end);
			if (!env_temp[index_temp])
				return (NULL);
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
			return (NULL);
		index++;
	}
	return (env_temp);
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
				splitted_line[index] = remove_quotes_string(splitted_line, index);
				break ;
			}
			index_x++;
		}
		index++;
	}
	return (splitted_line);
}
