#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int	g_exit_status;

void	main_execute_input(t_minishell *shell, char *line)
{
	add_history(line);
	shell->cmd_lst = lexing(line, shell->env_cpy);
	if (!shell->cmd_lst)
	{
		g_exit_status = -1;
		return ;
	}
	printing_lexer(shell->cmd_lst);
	if (is_builtin(shell->cmd_lst) == EXIT)
	{
		ft_putstr_fd("exit\n", STDIN_FILENO);
		exit(0);
	}
	g_exit_status = execute_cmds(shell, shell->cmd_lst, shell->env_cpy);
	free_ll(&shell->cmd_lst);
}

void	main_input_error(int *terminate)
{
	rl_clear_history();
	*terminate = 1;
	exit(1);
}

void	display_prompt(t_minishell *shell)
{
	char	*line;
	int		terminate;

	terminate = 0;
	init_ascii_art();
	remove_ctl_echo();
	while (!terminate)
	{
		if (g_exit_status == 0)
			line = readline("\033[0;37m \033[1m ZALGOSHELL_>\033[0m ");
		else
			line = readline(CURSED);
		if (line == NULL && terminate != 1)
			main_input_error(&terminate);
		else if (line[0] != '\0' && terminate != 1)
			main_execute_input(shell, line);
		else
			free(line);
	}
	rl_clear_history();
	if (line)
		free(line);
}

t_minishell	init_minishell(int argc, char *envp[])
{
	t_minishell	shell;

	if (argc != 1)
	{
		ft_printf("executable: too many arguments. \
			Executable can only be run as follows: './minishell'\n");
		exit(1);
	}
	shell.cmd_lst = malloc(sizeof(t_lexer));
	if (!shell.cmd_lst)
	{
		ft_printf("malloc: could not allocate memory for t_minishell shell\n");
		exit(1);
	}
	shell.env_cpy = copy_double_array(envp);
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
