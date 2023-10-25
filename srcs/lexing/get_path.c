/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:21 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/25 15:47:06 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_strcpy(temp, paths[index]);
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
	if (!paths)
		return (NULL);
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

char	*get_path_of_command(char *command, char **env_cpy)
{
	char	*get_path;
	char	**paths;
	char	*command_path;

	get_path = ft_getenv("PATH", env_cpy);
	if (!get_path)
		return (NULL);
	paths = ft_split(get_path, ':');
	free(get_path);
	if (!paths)
		return (NULL);
	command_path = find_path_loop(paths, command);
	free_double_array(paths);
	return (command_path);
}
