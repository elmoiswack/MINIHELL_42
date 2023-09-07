#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

//Global array - used to print out the enum strings. Must be deleted before handing in the project.
static const char *g_enum[] = {
[PIPE_READ] = "READ", //0
[PIPE_WRITE] = "WRITE", //1
[INFILE] = "INFILE", //2
[OUTFILE] = "OUTFILE", //3
[COMMAND] = "COMMAND", //4
[FLAG] = "FLAG", //5
[PIPE] = "PIPE", //6
[ENV_VAR] = "ENV_VAR", //7
[DELIMITER] = "DELIMITER",//8
[APPENDER] = "APPENDER", //9
[REDIRECT_IN] = "REDIRECT_IN", //10
[REDIRECT_OUT] = "REDIRECT_OUT", //11
[NONE] = "NONE", //12
[APPEND] = "APPEND", //13
[STDIN_IN] = "STDIN", //14
[STDOUT_OUT] = "STDOUT", //15
};

static void	route_input(int in, t_lexer *node)
{
	int infile;
	int hd_fd;

	if (node->delim)
	{
		if ((hd_fd = open("./data/heredoc.tmp", O_RDONLY)) < 0)
			perror("Cannot create temporary heredoc.tmp");
		if (dup2(hd_fd, STDIN_FILENO) < 0)
			perror("dup2");
		close(hd_fd);
	}
	if (node->input == INFILE)
	{
		if ((infile = open(node->file, O_RDONLY)) < 0)
		{
			perror("infile");
			exit(1);
		}
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

static void	run_child_process(int in, int out, t_lexer *node, char *envp[])
{
	route_input(in, node);
	route_output(out, node);
	if (check_access(node->content[0]) == -1)
		error_command_not_found(node->content[0]);
	else if (execve(node->path, node->content, envp) < 0)
		perror("execve");
	exit(-1);
}

void	print_cmd_lst(t_lexer *head)
{
	t_lexer	*current;
	int		n;

	current = head;
	n = 0;
	fprintf(stderr, "\033[0;36m--------EXECUTIONER--------\n");
	fprintf(stderr, "PROCESS\tCMD\tINPUT\tOUTPUT\tFILE\n");
	while (current)
	{
		fprintf(stderr, "%d\t%s\t%s\t%s\t%s\n", n, current->content[0], g_enum[current->input], g_enum[current->output], current->file);
		n++;
		current = current->next;
	}
	fprintf(stderr, "---------------------------\033[0m\n");
}

int	execute_cmds(t_lexer *head, char *envp[])
{
	t_lexer	*current;
	pid_t	pid;
	int		pipe_fd[2];
	int		prev_pipe;
	int		status;

	pid = 1;
	prev_pipe = STDIN_FILENO;
	current = head;
	if (!current->path && !current->delim)
		return (error_command_not_found(current->content[0]), 127);
	if (current->delim)
		create_heredoc_tmp(current->delim, envp);
	print_cmd_lst(head);
	while (current)
	{
		if (pipe(pipe_fd) < 0)
			perror("pipe");
		pid = fork();
		if (pid == 0)
		{
			catch_signals_child();
			run_child_process(prev_pipe, pipe_fd[PIPE_WRITE], current, envp);
		}
		close(pipe_fd[PIPE_WRITE]);
		prev_pipe = pipe_fd[PIPE_READ];
		current = current->next;
	}
	close(prev_pipe);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1);
	if (head->delim)
		clean_tmp_files(envp);
	return (WEXITSTATUS(status));
}
