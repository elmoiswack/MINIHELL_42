#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_var_expander(char **splitted_line)
{
	int	index;

	index = 0;
	while (splitted_line[index])
	{
		if (splitted_line[index][0] == '$' \
			&& ft_isalpha(splitted_line[index][1]) == 1)
			return (1);
		index++;
	}
	return (-1);
}

char	*remove_dollar(char **splitted_line, int index)
{
	int		index_te;
	int		index_sp;
	char	*temp;

	index_te = 0;
	index_sp = 1;
	temp = ft_calloc(ft_strlen(splitted_line[index]), sizeof(char));
	if (!temp)
		return (NULL);
	while (splitted_line[index][index_sp])
	{
		temp[index_te] = splitted_line[index][index_sp];
		index_te++;
		index_sp++;
	}
	return (temp);
}

int	get_index_var(char **splitted_line)
{
	int	index;

	index = 0;
	while (splitted_line[index])
	{
		if (splitted_line[index][0] == '$' \
			&& ft_isalpha(splitted_line[index][1]) == 1)
			break ;
		index++;
	}
	return (index);	
}

char	**replace_var_expander(char **splitted_line)
{
	int		index;
	char	*temp;
	char	*env_temp;

	index = get_index_var(splitted_line);
	temp = remove_dollar(splitted_line, index);
	env_temp = getenv(temp);
	if (!env_temp)
	{
		free_double_array(splitted_line);
		return (NULL);
	}
	free(temp);
	temp = ft_calloc(ft_strlen(env_temp) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_strcpy(temp, env_temp);
	free(splitted_line[index]);
	splitted_line[index] = temp;
	return (splitted_line);
}
