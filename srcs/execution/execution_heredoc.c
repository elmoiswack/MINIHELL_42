/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   execution_heredoc.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:54:55 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 21:54:38 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	write_to_heredoc(char *delim, char *env_cpy[], int heredoc_tmp)
{
	char	*heredoc_line;

	while (1)
	{
		heredoc_line = readline("> ");
		if (heredoc_line == NULL)
		{
			ft_printf("warning: here-document delimited by end-of-file (CTRL+D) \
instead of '%s'\n", delim);
			break ;
		}
		else if ((ft_strncmp(heredoc_line, delim, (ft_strlen(delim)
						+ ft_strlen(heredoc_line))) == 0))
			break ;
		heredoc_line = expand_heredoc_line(heredoc_line, env_cpy);
		ft_putstr_fd_nl(heredoc_line, heredoc_tmp);
		free(heredoc_line);
	}
	close(heredoc_tmp);
	exit (0);
}

static void	create_heredoc_tmp(char *delim, char *env_cpy[])
{
	int		heredoc_tmp;

	change_permission_heredoc_tmp();
	heredoc_tmp = open("./data/heredoc.tmp",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_tmp < 0)
		return (perror("heredoc_tmp"));
	write_to_heredoc(delim, env_cpy, heredoc_tmp);
}

static int	loop_through_heredocs(t_lexer *head, char *env_cpy[])
{
	t_lexer	*current;
	int		i;
	int		pid;

	i = 0;
	pid = 1;
	current = head;
	while (current && current->delim && current->delim[i])
	{
		pid = fork();
		if (pid == 0)
		{
			change_signal_profile(HD);
			create_heredoc_tmp(current->delim[i], env_cpy);
		}
		if (fetch_exit_status_hd(pid, head, env_cpy) != 0)
			return (1);
		i++;
		if (!current->delim[i])
		{
			current = current->next;
			i = 0;
		}
	}
	return (fetch_exit_status_hd(pid, head, env_cpy));
}

int	create_heredoc_loop(t_lexer *head, char *env_cpy[])
{
	int	err;

	err = 0;
	if (!head->delim)
		return (0);
	else
		return (err = loop_through_heredocs(head, env_cpy));
}
