/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_pwd.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:24:07 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/24 12:25:35 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PWD_SIZE 256

static void	pwd(char *cwd)
{
	int		cd_len;
	int		total_len;

	cd_len = ft_strlen(ft_strrchr(cwd, '/'));
	total_len = ft_strlen(cwd);
	write(1, cwd, total_len - cd_len);
	write(1, "\033[0;31m", 8);
	write(1, ft_strrchr(cwd, '/'), ft_strlen(ft_strrchr(cwd, '/')));
	write(1, "\033[0m\n", 6);
	free(cwd);
	return ;
}

int	execute_pwd(char *env_cpy[])
{
	char	*cwd;

	cwd = ft_getenv("PWD", env_cpy);
	if (!cwd)
		return (perror("getcwd()"), 1);
	else
		return (pwd(cwd), 0);
	if (getcwd(cwd, PWD_SIZE) == NULL)
		return (perror("getcwd()"), 1);
	else
		return (pwd(cwd), 0);
}
