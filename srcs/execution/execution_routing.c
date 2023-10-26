/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   execution_routing.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:54:11 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/26 11:11:14 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	redirect_from_to(int fd_from, int fd_to) // To do: close fd when dup2 fails
{
	if (dup2(fd_from, fd_to) < 0)
	{
		perror("dup2");
		close (fd_from);
	}
}

static void	route_infiles(t_lexer *node)
{
	int	infile;
	int	i;

	i = 0;
	while (node->infile[i])
	{
		infile = open(node->infile[i], O_RDONLY);
		if (infile < 0)
		{
			perror("infile");
			exit(1);
		}
		redirect_from_to(infile, STDIN_FILENO);
		close(infile);
		i++;
	}
}

static void	route_outfiles(t_lexer *node, int flags, mode_t mode)
{
	int	outfile;
	int	i;

	i = 0;
	while (node->outfile[i])
	{
		outfile = open(node->outfile[i], flags, mode);
		if (outfile < 0)
			perror("outfile");
		redirect_from_to(outfile, STDOUT_FILENO);
		close(outfile);
		i++;
	}
}

void	route_input(int in, t_lexer *node)
{
	int	hd_fd;

	if (node->delim)
	{
		hd_fd = open("./data/heredoc.tmp", O_RDONLY);
		if (hd_fd < 0)
			perror("Cannot create temporary heredoc.tmp");
		redirect_from_to(hd_fd, STDIN_FILENO);
		close(hd_fd);
	}
	if (node->input == INFILE)
		route_infiles(node);
	else if (node->input == PIPE_READ)
		redirect_from_to(in, STDIN_FILENO);
	if (node->cmd_id >= 1)
		close(in);
}

void	route_output(int out, t_lexer *node)
{
	if (node->output == OUTFILE)
		route_outfiles(node, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->output == APPEND)
		route_outfiles(node, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->output == PIPE_WRITE)
		redirect_from_to(out, STDOUT_FILENO);
	close(out);
}
