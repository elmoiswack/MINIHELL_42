#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

static void	run_cmd(char *path, char *content[], char *env_cpy[])
{
	if (execve(path, content, env_cpy) < 0)
		perror("execve");
}

static void	run_child_process(int in, int out, t_lexer *node,
		t_minishell *shell)
{
	t_builtin	builtin;
	int			err;

	err = -1;
	builtin = is_builtin(node);
	route_input(in, node);
	route_output(out, node);
	node->content = colorize_cmd(node->content);
	if (is_absolute_path(node))
		run_cmd(node->path, node->content, shell->env_cpy);
	if (builtin != NO_BUILTIN)
		err = execute_builtin(shell, builtin);
	else if (!cmd_exists(node->content[0], shell->env_cpy))
		err = error_command_not_found(node->content[0]);
	else
		run_cmd(node->path, node->content, shell->env_cpy);
	clean_up(shell);
	exit(err);
}

static int	fetch_exit_status(pid_t pid, t_lexer *head, char *env_cpy[]) // To do: add exit for 130!
{
	int		status;

	status = 0;
	waitpid(pid, &status, 0);
	ft_printf("WTERMSIG(status): %d\n WIFISIGNALED(status): %d\nWTERMSIG(status): %d\n", WTERMSIG(status), WIFSIGNALED(status), WTERMSIG(status));
	if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
		return (change_signal_profile(PARENT), 131);
	else if (WIFSIGNALED(status) && WTERMSIG(status) >= 7)
		return (change_signal_profile(PARENT), 130);
	while (wait(NULL) != -1)
		;
	clean_tmp_files(head, env_cpy);
	return (change_signal_profile(PARENT), WEXITSTATUS(status));
}

static pid_t	run_and_route_processes(pid_t pid, t_lexer *head,
		t_lexer *current, t_minishell *shell)
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
		change_signal_profile(WAITING);
		if (pid == 0)
		{
			change_signal_profile(CHILD);
			run_child_process(prev_pipe, pipe_fd[PIPE_WRITE], current, shell);
		}
		close(pipe_fd[PIPE_WRITE]);
		prev_pipe = pipe_fd[PIPE_READ];
		current = current->next;
	}
	close(prev_pipe);
	return (pid);
}

int	execute_cmds(t_minishell *shell, t_lexer *head, char *envp[])
{
	t_lexer	*current;
	pid_t	pid;

	pid = 1;
	current = head;
	if (create_heredoc_loop(current, envp) != 0)
		return (130);
	print_cmd_lst(head);
	pid = run_and_route_processes(pid, head, current, shell);
	return (fetch_exit_status(pid, head, envp));
}
