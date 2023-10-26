/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   execution_processes.c                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 17:48:36 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/26 12:12:52 by fvan-wij      ########   odam.nl         */
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
#include <errno.h>

static void	run_cmd(char *path, char *content[], char *env_cpy[])
{
	if (execve(path, content, env_cpy) < 0)
		perror("execve");
}

static void	run_child_process(int in, int *pipe_fd, t_lexer *node,
		t_minishell *shell)
{
	t_builtin	builtin;
	int			err;

	err = -1;
	builtin = is_builtin(node);
	change_signal_profile(CHILD);
	close(pipe_fd[PIPE_READ]);
	route_input(in, node);
	route_output(pipe_fd[PIPE_WRITE], node);
	node->content = colorize_cmd(node->content);
	if (is_absolute_path(node))
		run_cmd(node->path, node->content, shell->env_cpy);
	if (builtin != NO_BUILTIN)
		err = execute_builtin(shell, builtin, node);
	else if (!cmd_exists(node->content[0], shell->env_cpy))
		err = err_log(E_CMDNFND, (node->content[0]));
	else
		run_cmd(node->path, node->content, shell->env_cpy);
	clean_up(shell);
	exit(err);
}

static int	cmd_amount(t_lexer *head)
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

static int	wait_on_child_processes(t_lexer *head, pid_t *pid, int status)
{
	int		i;

	i = 0;
	while (i < cmd_amount(head))
	{
		status = 0;
		waitpid(pid[i], &status, 0);
		i++;
	}
	return (status);
}

static int	fetch_exit_status(pid_t *pid, t_lexer *head)
{
	int		status;

	status = 0;
	status = wait_on_child_processes(head, pid, status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (change_signal_profile(PARENT), 131);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (change_signal_profile(PARENT), 130);
	else
		return (change_signal_profile(PARENT), WEXITSTATUS(status));
}

static pid_t	*run_and_route_processes(pid_t *pid, t_lexer *head, t_minishell *shell)
{
	t_lexer	*current;
	int		pipe_fd[2];
	int		prev_pipe;
	size_t	i;

	prev_pipe = STDIN_FILENO;
	current = head;
	i = 0;
	while (current)
	{
		if (pipe(pipe_fd) < 0)
			perror("pipe()");
		pid[i] = fork(); 
		if (pid[i] < 0)
			return (perror("fork()"), pid);
		change_signal_profile(WAITING);
		if (pid[i] == 0)
			run_child_process(prev_pipe, pipe_fd, current, shell);
		close(pipe_fd[PIPE_WRITE]);
		if (current->cmd_id >= 1)
			close(prev_pipe);
		prev_pipe = pipe_fd[PIPE_READ];
		current = current->next;
	}
	close(prev_pipe);
	return (pid);
}

pid_t	*allocate_pid_array(t_lexer *head)
{
	pid_t	*pid;
	int		n;

	n = cmd_amount(head);
	pid = malloc(sizeof(pid_t) * n);
	if (!pid)
		return (NULL);
	else
		return (pid);
	ft_memset(pid, 1, sizeof(pid));
}


int	execute_cmds(t_minishell *shell, t_lexer *head, char *env_cpy[])
{
	pid_t	*pid;

	pid = allocate_pid_array(head);
	if (!pid)
		return(err_log(E_ALLOC, "'pid array'"));
	print_cmd_lst(head);
	if (create_heredoc_loop(head, env_cpy) != 0)
		return (130);
	pid = run_and_route_processes(pid, head, shell);
	clean_tmp_files(head, env_cpy);
	return (fetch_exit_status(pid, head));
}
