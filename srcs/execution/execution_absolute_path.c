#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int	check_access(char *cmd, char *env_cpy[])
{
	int		i;
	char	**paths;
	char	*temp;
	char	*slash_cmd;
	char	*env;

	i = -1;
	env = ft_getenv("PATH", env_cpy);
	if (!env)
		return (-1);
	paths = ft_split(env, ':');
	free(env);
	slash_cmd = ft_strjoin("/", cmd);
	while (paths[++i])
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
	}
	free_double_array(paths);
	return (free(slash_cmd), -1);
}

int	is_absolute_path(t_lexer *node)
{
	if (access(node->content[0], X_OK) == 0 && !node->path)
		return (1);
	else
	 	return (-1);
}

void	parse_node_absolute_path(t_lexer *node)
{
	if (!node->path)
		node->path = ft_strdup(node->content[0]);
	char *new_cmd = (ft_strrchr(node->content[0], '/') + 1);
	node->content[0] = new_cmd;
}
