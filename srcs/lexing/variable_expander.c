#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**one_case(char **double_array, int index, char **env_cpy)
{
	char	*temp;
	char	*env_temp;

	temp = remove_dollar(double_array, index);
	env_temp = ft_getenv(temp, env_cpy);
	free(temp);
	if (!env_temp)
	{
		free_double_array(double_array);
		return (NULL);
	}
	temp = ft_calloc(ft_strlen(env_temp) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_strcpy(temp, env_temp);
	free(double_array[index]);
	double_array[index] = temp;
	return (double_array);
}

char	**which_case_env(char **splitted_line, int index, char **env_cpy)
{
	if (splitted_line[index][0] == '"')
		splitted_line[index] = remove_quotes_string(splitted_line, index);
	if (!splitted_line[index])
		return (NULL);
	if (check_multiple_env(splitted_line, index) == 1 && are_there_spaces(splitted_line, index) != 1)
		return (one_line_multenv(splitted_line, index, env_cpy));
	if (check_multiple_env(splitted_line, index) == 1 || check_env_in_string(splitted_line, index) == 1)
		return (mult_line_multenv(splitted_line, index, env_cpy));
	return (one_case(splitted_line, index, env_cpy));
}

char	**replace_var_expander(t_lexer *info_list, char **splitted_line, char **env_cpy)
{
	int	index;
	int	index_x;

	index = 0;
	while (splitted_line[index])
	{
		index_x = 0;
		while (splitted_line[index][index_x])
		{
			if (splitted_line[index][0] == 39)
			{
				splitted_line[index] = remove_quotes_string(splitted_line, index);
				break ;
			}
			if (splitted_line[index][index_x] == '$')
			{
				splitted_line = which_case_env(splitted_line, index, env_cpy);
				break ;
			}
			index_x++;
		}
		if (!splitted_line)
		{
			set_error_lex(info_list, 1, "Enviromental variable doesn't exist!");
			return (NULL);
		}
		index++;
	}
	return (splitted_line);
}
