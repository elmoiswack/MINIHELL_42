/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_pwd.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:24:07 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/17 12:25:31 by fvan-wij      ########   odam.nl         */
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
	return ;
}

int	execute_pwd(t_minishell *shell)
{
	char	cwd[PWD_SIZE];
	char	*temp;

	if (getcwd(cwd, PWD_SIZE) == NULL)
	{
		temp = ft_getenv("PWD", shell->env_cpy);
		if (!temp)
			return (err_log(E_ERR, "PWD is not set"), 1);
		pwd(temp);
		return (free(temp), 0);
	}
	else
		return (pwd(cwd), 0);
}
