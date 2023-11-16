/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utilities_misc2.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/26 13:13:27 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/16 15:43:54 by fvan-wij      ########   odam.nl         */
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
	struct stat path_stat;
	if (stat(content, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}
