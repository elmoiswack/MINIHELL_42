#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static void	route_input(int in, t_lexer *node)
{
	int infile;

	if (node->input == INFILE)
	{
		if ((infile = open(node->file, O_RDONLY)) < 0)
			perror("infile");
		if (dup2(infile, STDIN_FILENO) < 0)
			perror("dup2");
		close(infile);
	}
	else if (node->input == PIPE_READ)
	{
		if (dup2(in, STDIN_FILENO) < 0)
			perror("dup2");
	}
}

static void	route_output(int out, t_lexer *node)
{
	int outfile;

	if (node->output == OUTFILE)
	{
		if ((outfile = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			perror("outfile");
		if (dup2(outfile, STDOUT_FILENO) < 0)
			perror("dup2");
		close(outfile);
	}
	else if (node->output == APPEND)
	{
		if ((outfile = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
			perror("outfile");
		if (dup2(outfile, STDOUT_FILENO) < 0)
			perror("dup2");
		close(outfile);
	}
	else if (node->output == PIPE_WRITE)
	{
		if (dup2(out, STDOUT_FILENO) < 0)
			perror("dup2");
	}
	close(out);
}

static void	run_child_process(int in, int out, t_lexer *node, char *envp[], int n)
{
	fprintf(stderr, "PROCES[%d]: node->input %d,\tnode->output %d,\tnode->file %s\n", n, node->input, node->output, node->file);
	route_input(in, node);
	route_output(out, node);
	if (execve(node->path, node->content, envp) < 0)
		perror("execve");
	exit(-1);
}

int	execute_cmds(t_lexer *head, char *envp[])
{
	t_lexer	*current;
	pid_t	pid;
	int		pipe_fd[2];
	int		prev_pipe;
	int		status;
	int		n;

	pid = 1;
	prev_pipe = STDIN_FILENO;
	n = 0;
	// copy_envp = copy_double_array(envp);
	current = head;
	if (current->delim)
		create_heredoc_tmp(current->delim);
	fprintf(stderr, "--------EXECUTIONER--------\n");
	while (current)
	{
		if (pipe(pipe_fd) < 0)
			perror("pipe");
		pid = fork();
		if (pid == 0)
			run_child_process(prev_pipe, pipe_fd[PIPE_WRITE], current, envp, n);
		close(pipe_fd[PIPE_WRITE]);
		prev_pipe = pipe_fd[PIPE_READ];
		n++;
		current = current->next;
	}
	close(prev_pipe);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1);
	fprintf(stderr, "---------------------------\n");
	return (WEXITSTATUS(status));
}
