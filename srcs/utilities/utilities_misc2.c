/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utilities_misc2.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/26 13:13:27 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/17 12:28:34 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool	is_directory(char *content)
{
	struct stat	path_stat;

	if (stat(content, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

void	add_env(t_minishell *shell, char *env)
{
	shell->env_cpy = ft_append_to_double_array(shell->env_cpy, env);
	if (!shell->env_cpy)
		err_log(E_ERR, "add_env()");
}

void	go_to_home(char *env_cpy[])
{
	char	*temp;

	temp = ft_getenv("HOME", env_cpy);
	if (!temp)
		err_log(E_ERR, "cd: HOME not set");
	else if (chdir(temp) == -1)
		perror("chdir()");
	free (temp);
}
