#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	run_child_process(int in, int out, t_lexer *node, t_minishell *shell)
{
	t_builtin builtin;

	route_input(in, node);
	route_output(out, node);
	builtin = is_builtin(node);
	if (builtin != NO_BUILTIN)
	{
		execute_builtin(shell, builtin);
		exit(0);
	}
	if (check_access(node->content[0]) == -1)
	{
		clean_up(shell);
		return (error_command_not_found(node->content[0]));
	}
	else if (execve(node->path, node->content, shell->env_cpy) < 0)
		perror("execve");
	exit(-1);
}

static pid_t	run_and_route_processes(pid_t pid, t_lexer *head, t_lexer *current, t_minishell *shell)
{
	int		pipe_fd[2];
	int		prev_pipe;

	prev_pipe = STDIN_FILENO;
	current = head;
	while (current)
	{
		if (pipe(pipe_fd) < 0)
			perror("pipe");
		pid = fork();
		if (pid == 0)
		{
			catch_signals_child();
			run_child_process(prev_pipe, pipe_fd[PIPE_WRITE], current, shell);
		}
		close(pipe_fd[PIPE_WRITE]);
		prev_pipe = pipe_fd[PIPE_READ];
		current = current->next;
	}
	catch_signals_parent();
	close(prev_pipe);
	return (pid);
}

static int	fetch_exit_status(pid_t pid, t_lexer *head, char *env_cpy[])
{
	int		status;

	waitpid(pid, &status, 0);
	while (wait(NULL) != -1);
	clean_tmp_files(head, env_cpy);
	return (WEXITSTATUS(status));
}

int	execute_cmds(t_minishell *shell, t_lexer *head, char *envp[])
{
	t_lexer	*current;
	pid_t	pid;

	pid = 1;
	current = head;
	create_heredoc_loop(current, envp);
	print_cmd_lst(head);
	pid = run_and_route_processes(pid, head, current, shell);
	return (fetch_exit_status(pid, head, envp));
}
