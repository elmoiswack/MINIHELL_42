/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_processes.c                             :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:09:48 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/17 10:26:37 by fvan-wij      ########   odam.nl         */
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

static int	run_cmd(char *path, char *content[], char *env_cpy[])
{
	change_signal_profile(CHILD);
	if (execve(path, content, env_cpy) < 0)
		perror("execve");
	return (errno);
}

static void	run_child_process(int in, int *pipe_fd, t_lexer *node,
		t_minishell *shell)
{
	t_builtin	builtin;
	int			err;

	err = -1;
	builtin = is_builtin(node);
	close(pipe_fd[PIPE_READ]);
	route_input(in, node);
	route_output(pipe_fd[PIPE_WRITE], node);
	if (!node->content || node->content[0][0] == '\0')
		exit (err);
	else if (is_directory(node->content[0]))
		err = err_log(E_DIR, node->content[0]);
	else if (is_absolute_path(node))
		err = run_cmd(node->path, node->content, shell->env_cpy);
	else if (builtin != NO_BUILTIN)
		err = execute_builtin(shell, builtin, node);
	else if (!cmd_exists(node->content[0], shell->env_cpy))
		err = err_log(E_CMDNFND, (node->content[0]));
	else
	{
		node->content = colorize_cmd(node->content);
		err = run_cmd(node->path, node->content, shell->env_cpy);
	}
	free_ll(&shell->cmd_lst);
	exit(err);
}

static int	fetch_exit_status(pid_t *pid, t_lexer *head)
{
	int		status;

	status = 0;
	status = wait_on_child_processes(head, pid, status);
	free(pid);
	unlink("./data/heredoc.tmp");
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (change_signal_profile(PARENT), 130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (change_signal_profile(PARENT), 131);
	else
		return (change_signal_profile(PARENT), WEXITSTATUS(status));
}

static pid_t	*run_and_route_processes(pid_t *pid, t_lexer *head,
		t_minishell *shell)
{
	t_lexer	*current;
	int		pipe_fd[2];
	int		prev_pipe;
	int		i;

	prev_pipe = STDIN_FILENO;
	current = head;
	i = 0;
	while (current)
	{
		if (pipe(pipe_fd) < 0)
			perror("pipe()");
		pid[i] = create_child_process();
		change_signal_profile(WAITING);
		if (pid[i] == 0)
			run_child_process(prev_pipe, pipe_fd, current, shell);
		close(pipe_fd[PIPE_WRITE]);
		if (current->cmd_id >= 1)
			close(prev_pipe);
		prev_pipe = pipe_fd[PIPE_READ];
		current = current->next;
		i++;
	}
	return (close(prev_pipe), pid);
}

int	execute_cmds(t_minishell *shell, t_lexer *head, char *env_cpy[])
{
	pid_t	*pid;

	pid = allocate_pid_array(cmd_amount(head));
	if (!pid)
		return (err_log(E_ALLOC, "'pid array'"));
	if (create_heredoc_loop(head, env_cpy) != 0)
		return (free(pid), 130);
	pid = run_and_route_processes(pid, head, shell);
	return (fetch_exit_status(pid, head));
}
