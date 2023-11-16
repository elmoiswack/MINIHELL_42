/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   execution_absolute_path.c                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:36:19 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/16 13:29:36 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

static bool	is_cmd_executable(char *paths[], char *slash_cmd)
{
	int		i;
	char	*temp;

	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], slash_cmd);
		if (access(temp, X_OK) == 0)
		{
			free_double_array(paths);
			free(temp);
			return (free(slash_cmd), true);
		}
		else
			free(temp);
	}
	free_double_array(paths);
	return (free(slash_cmd), false);
}

bool	cmd_exists(char *cmd, char *env_cpy[])
{
	char	**paths;
	char	*slash_cmd;
	char	*env;

	env = ft_getenv("PATH", env_cpy);
	if (!env)
		return (false);
	paths = ft_split(env, ':');
	free(env);
	slash_cmd = ft_strjoin("/", cmd);
	return (is_cmd_executable(paths, slash_cmd));
}

bool	is_absolute_path(t_lexer *node)
{
	if (access(node->content[0], X_OK) == 0 && !node->path)
		return (parse_node_absolute_path(node), true);
	else
		return (false);
}

void	parse_node_absolute_path(t_lexer *node)
{
	char	*new_cmd;

	new_cmd = NULL;
	if (!node->path)
		node->path = ft_strdup(node->content[0]);
	if (!node->path)
	{
		err_log(E_ALLOC, "strdup");
		return ;
	}
	new_cmd = (ft_strrchr(node->content[0], '/') + 1);
	node->content[0] = new_cmd;
}
