#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int g_exit_status;

void	display_prompt(t_minishell *shell)
{	
	char	*line;
	int		terminate;
	t_builtin builtin;

	terminate = 0;
	init_ascii_art();
	remove_ctl_echo();
	while (!terminate)
	{
		if (g_exit_status == 0)	
			line = readline("\033[0;37m \033[1m MINIHELL_>\033[0m ");
		else
			line = readline("\033[0;31m \033[1m Ç̈ͮ̾ͫ̆ͯ̏U̷͂̎Rͩ̀S̶̽ͮ̑̋̉ͩ̃Ë̷́̓̾͆ͫḐ͒̆̚̚_ >\033[0m ");
		if (line == NULL)
		{
			free(line);
			terminate = 1;
		}
		else if (line[0] != '\0')
		{
			add_history(line);
			shell->cmd_lst = lexing(line, shell->env_cpy);
			if (!shell->cmd_lst)
			{
				printf("fuck\n");
				free(line);
				continue ;	
			}
			printing_lexer(shell->cmd_lst);
			builtin = is_builtin(shell->cmd_lst);
			if (builtin != NO_BUILTIN && !shell->cmd_lst->next)
				execute_builtin(shell, builtin);
			else
				g_exit_status = execute_cmds(shell, shell->cmd_lst, shell->env_cpy);
			free_ll(&shell->cmd_lst);
		}
		else
			free(line);
	}
}

t_minishell	init_minishell(int argc, char *argv[], char *envp[])
{
	t_minishell shell;

	(void) argv;
	if (argc != 1)
	{
		ft_printf("executable: too many arguments. Executable can only be run as follows: './minishell'\n");
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
	return (shell);
}

// void f()
// {
// 	system("leaks minishell");
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	shell;
	
	// atexit(f);
	shell = init_minishell(argc, argv, envp);
	catch_signals_parent();
	display_prompt(&shell);
	free_double_array(shell.env_cpy);
	return (0);
}
