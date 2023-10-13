#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*replace_vars_loop(char *line, char *new_line, \
	char **env_temp, int index)
{
	int	index_new;
	int	index_env;
	int	end;

	index_new = 0;
	index_env = 0;
	while (line[index])
	{
		if (line[index] == '$')
		{
			end = get_env_end(line, index + 1);
			new_line = put_env_in_line(new_line, index_new, \
				env_temp, index_env);
			index_new += ft_strlen(env_temp[index_env]);
			index_env++;
			index = end;
		}
		if (line[index] && line[index] != '$')
		{
			new_line[index_new] = line[index];
			index_new++;
			index++;
		}
	}
	return (new_line);
}

char	*replace_variables(char *line, char **env_temp)
{
	char	*new_line;
	int		index;

	index = 0;
	new_line = ft_calloc(get_size_strings(line, env_temp) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	new_line = replace_vars_loop(line, new_line, env_temp, index);
	free(line);
	return (new_line);
}

char	*get_env_var(char *line, char **env_cpy, int ammount_env)
{
	// int		index;
	char	**env_temp;
	// int		index_tmp;

	// index = 0;
	// index_tmp = 0;
	env_temp = ft_calloc(ammount_env + 1, sizeof(char *));
	if (!env_temp)
		return (NULL);
	env_temp = fill_array_env(line, ammount_env, env_temp, 0);
	if (!env_temp)
		return (NULL);
	env_temp = expand_env_variables(env_temp, env_cpy);
	if (!env_temp)
	{
		free(line);
		return (NULL);
	}
	line = replace_variables(line, env_temp);
	if (!line)
		return (NULL);
	free_double_array(env_temp);
	return (line);
}

char	*env_expander_loop(char **splitted_line, int index, char **env_cpy)
{
	int	index_x;

	index_x = 0;
	if (splitted_line[index][0] == '\'')
	{
		splitted_line[index] = remove_quotes_string(splitted_line, index);
		return (splitted_line[index]);
	}
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] == '$')
		{
			splitted_line[index] = get_env_var(splitted_line[index], \
				env_cpy, how_many_env_var(splitted_line[index]));
			break ;
		}
		index_x++;
	}
	return (splitted_line[index]);
}

char	**replace_var_expander(t_lexer *info_list, char **splitted_line, \
	char **env_cpy)
{
	int	index;

	index = 0;
	while (splitted_line[index])
	{
		splitted_line[index] = env_expander_loop(splitted_line, index, env_cpy);
		if (!splitted_line[index])
		{
			free_double_array(splitted_line);
			error_lex(info_list, 1, "");
			return (NULL);
		}
		index++;
	}
	splitted_line = check_quotes_env(splitted_line);
	return (splitted_line);
}
