/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:30:25 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/11/01 12:39:12 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	main_execute_input(t_minishell *shell, char *line)
{
	t_builtin	builtin;

	add_history(line);
	add_to_history_file(line);
	shell->cmd_lst = lexing(line, shell->env_cpy);
	if (!shell->cmd_lst)
	{
		err_log(E_ALLOC, NULL);
		shell->status = -1;
		return ;
	}
	add_cmd_id(shell->cmd_lst);
	builtin = is_builtin(shell->cmd_lst);
	if (builtin != NO_BUILTIN && !shell->cmd_lst->next
		&& !shell->cmd_lst->infile && !shell->cmd_lst->outfile)
		shell->status = execute_builtin(shell, builtin, shell->cmd_lst);
	else
		shell->status = execute_cmds(shell, shell->cmd_lst, shell->env_cpy);
	free_ll(&shell->cmd_lst);
}

void	main_input_error(int *terminate)
{
	rl_clear_history();
	*terminate = 1;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(0);
}

void	display_prompt(t_minishell *shell)
{
	char	*line;
	int		terminate;

	terminate = 0;
	init_ascii_art();
	init_history();
	remove_ctl_echo();
	while (!terminate)
	{
		if (shell->status == 0)
			line = readline(NON_CURSED);
		else
			line = readline(CURSED);
		if (line == NULL)
			main_input_error(&terminate);
		else if (line[0] != '\0' && terminate != 1)
			main_execute_input(shell, line);
		else
			free(line);
	}
	if (line)
		free(line);
}

t_minishell	init_minishell(int argc, char *envp[])
{
	t_minishell	shell;

	if (argc != 1)
	{
		err_log(E_INPUT, NULL);
		exit(1);
	}
	shell.cmd_lst = malloc(sizeof(t_lexer));
	if (!shell.cmd_lst)
	{
		err_log(E_ALLOC, "'cmd_lst'");
		exit(1);
	}
	shell.env_cpy = ft_copy_double_array(envp);
	if (!shell.env_cpy)
		err_log(E_ALLOC, "'env_cpy'");
	if (export_content(Z_THEME, &shell) != 0)
		err_log(E_ALLOC, "'LS_COLORS'");
	shell.status = 0;
	shell.builtin = NO_BUILTIN;
	shell.profile = PARENT;
	change_signal_profile(PARENT);
	return (shell);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	shell;

	(void) argv;
	shell = init_minishell(argc, envp);
	display_prompt(&shell);
	free_double_array(shell.env_cpy);
	free_lexing_content_struct(shell.cmd_lst);
	free_lexing_struct(shell.cmd_lst);
	return (0);
}
