#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**put_slash_behind(char **paths)
{
	int		index;
	char	*temp;

	index = 0;
	while (paths[index])
	{
		temp = ft_calloc(ft_strlen(paths[index]) + 1, sizeof(char));
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, paths[index], ft_strlen(paths[index]) + 1);
		free(paths[index]);
		paths[index] = ft_strjoin(temp, "/");
		free(temp);
		if (!paths[index])
			return (NULL);
		index++;
	}
	return (paths);
}

char	*find_path_loop(char **paths, char *command)
{
	char	*temp;
	int		index;

	index = 0;
	paths = put_slash_behind(paths);
	while (paths[index])
	{
		temp = ft_strjoin(paths[index], command);
		if (!temp)
			return (NULL);
		if (access(temp, F_OK | X_OK) == 0)
			return (temp);
		free(temp);
		index++;
	}
	return (NULL);
}

char	*get_path_of_command(char *command)
{
	char	*get_path;
	char	**paths;
	char	*command_path;

	get_path = getenv("PATH");
	if (!get_path)
		return (NULL);
	paths = ft_split(get_path, ':');
	if (!paths)
		return (NULL);
	command_path = find_path_loop(paths, command);
	if (!command_path)
		return (NULL);
	free_2d_array(paths);
	return (command_path);
}
//kdasdas
