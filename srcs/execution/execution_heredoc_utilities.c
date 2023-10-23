/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   execution_heredoc_utilities.c                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 17:36:32 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 18:19:09 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void	change_permission_heredoc_tmp(void)
{
	pid_t		pid;
	char *const	chmod_args[] = {"chmod", "777", "./data/heredoc.tmp", NULL};

	if (access(chmod_args[2], F_OK) == 0)
	{
		pid = fork();
		if (pid == 0 && execve(get_path(chmod_args[0]), chmod_args, NULL) < 0)
			exit(-1);
	}
}

void	clean_tmp_files(t_lexer *head, char *envp[])
{
	char *const	rm_args[] = {"rm", "./data/heredoc.tmp", NULL};
	pid_t		pid;

	if (head->delim)
	{
		pid = fork();
		if (pid == 0 && execve(get_path(rm_args[0]), rm_args, envp) < 0)
		{
			perror("error cleanup tmp");
			exit(-1);
		}
	}
}

int	fetch_exit_status_hd(pid_t pid, t_lexer *head, char *env_cpy[])
{
	int		status;

	status = 0;
	waitpid(pid, &status, 0);
	// ft_printf("WEXITSTATUS(status): %d\n WIFSIGNALED(status): %d\n", WEXITSTATUS(status), WIFSIGNALED(status));
	while (wait(NULL) != -1)
		;
	if (WEXITSTATUS(status) != 0)
		return (clean_tmp_files(head, env_cpy), WEXITSTATUS(status));
	else
		return (0);
}
