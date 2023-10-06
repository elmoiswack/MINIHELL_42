#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*get_path(const char *cmd)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], ft_strjoin("/", cmd));
		if (access(temp, X_OK) == 0)
			return (temp);
		else
		 free(temp);
		i++;
	}
	return (NULL);
}

int	check_access(char *cmd)
{
	int		i;
	char	**paths;
	char	*temp;
	char	*slash_cmd;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], slash_cmd);
		if (access(temp, X_OK) == 0)
		{
			free_double_array(paths);
			free(temp);
			return (free(slash_cmd), 1);
		}
		else
			free(temp);
		i++;
	}
	free_double_array(paths);
	return (free(slash_cmd), -1);
}

char *ft_getenv(char *var_name, char **env)
{
	char	*value;
	int		var_index;
	
	var_index = var_exists(env, var_name);
	if (var_index == -1)
		return (NULL);
	else
		value = ft_strdup(ft_strchr(env[var_index], '=') + 1);
	return (value);
}

int	arg_is_env(char *raw_input, char **value, char *envp[])
{
	char	*temp;

	temp = ft_strdup(raw_input + 1);
	*value = ft_getenv(temp, envp);
	// free(temp);
	if (raw_input[0] == '$' && *value)
		return (1);
	else
	{
		free(temp);
		*value = NULL;
		return (0);
	}
}

int	var_exists(char	**env, char *var)
{
	int	i;
	int var_len;

	var_len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

