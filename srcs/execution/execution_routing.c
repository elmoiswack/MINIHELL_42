#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void	redirect_from_to(int fd_from, int fd_to)
{
	if (dup2(fd_from, fd_to) < 0)
		perror("dup2");
}

void	route_input(int in, t_lexer *node)
{
	int infile;
	int hd_fd;

	if (node->delim)
	{
		if ((hd_fd = open("./data/heredoc.tmp", O_RDONLY)) < 0)
			perror("Cannot create temporary heredoc.tmp");
		redirect_from_to(hd_fd, STDIN_FILENO);
		close(hd_fd);
	}
	if (node->input == INFILE)
	{
		if ((infile = open(node->file, O_RDONLY)) < 0)
		{
			perror("infile");
			exit(1);
		}
		redirect_from_to(infile, STDIN_FILENO);
		close(infile);
	}
	else if (node->input == PIPE_READ)
		redirect_from_to(in, STDIN_FILENO);
}

void	route_output(int out, t_lexer *node)
{
	int outfile;

	if (node->output == OUTFILE)
	{
		if ((outfile = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			perror("outfile");
		redirect_from_to(outfile, STDOUT_FILENO);
		close(outfile);
	}
	else if (node->output == APPEND)
	{
		if ((outfile = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
			perror("outfile");
		redirect_from_to(outfile, STDOUT_FILENO);
		close(outfile);
	}
	else if (node->output == PIPE_WRITE)
		redirect_from_to(out, STDOUT_FILENO);
	close(out);
}
