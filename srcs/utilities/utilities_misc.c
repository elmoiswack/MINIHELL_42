/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utilities_misc.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/26 13:13:27 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/26 16:58:01 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	add_cmd_id(t_lexer *head)
{
	t_lexer	*current;
	int		i;

	current = head;
	i = 0;
	while (current)
	{
		current->cmd_id = i;
		current = current->next;
		i++;
	}
}

int	cmd_amount(t_lexer *head)
{
	t_lexer	*current;
	int		i;

	current = head;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

pid_t	*allocate_pid_array(int n)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * n);
	if (!pid)
		return (NULL);
	else
		return (pid);
	ft_memset(pid, 1, sizeof(pid));
}

int	wait_on_child_processes(t_lexer *head, pid_t *pid, int status)
{
	int		i;
	i = 0;
	while (i < cmd_amount(head))
	{
		status = 0;
		waitpid(pid[i], &status, 0);
		// ft_printf("WIFEXITED(%d): %d, WIFSIGNALED(%d): %d, WTERMSIG(%d): %d\n", status, WIFEXITED(status), status, WIFSIGNALED(status), status, WTERMSIG(status));
		i++;
	}
	return (status);
}

pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork()"), -1);
	return (pid);
}
