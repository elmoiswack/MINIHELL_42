#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//Global array - used to print out the enum strings. Must be deleted before handing in the project.
static const char *g_enum[] = {
[PIPE_READ] = "PIPE_READ", //0
[PIPE_WRITE] = "PIPE_WRITE", //1
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

void	printing_lexer(t_lexer *info_lexer)
{
	int	index;

	if (!info_lexer)
		return ;
	fprintf(stderr, "\033[0;36m----------PARSER-----------");
	while(info_lexer)
	{
		fprintf(stderr, "\n");
		index = 0;
		while (info_lexer->content[index])
		{
			fprintf(stderr, "content[%d] = %s\n", index, info_lexer->content[index]);
			index++;
		}
		fprintf(stderr, "path = %s\n", info_lexer->path);
		fprintf(stderr, "file name = %s\n", info_lexer->file);
		fprintf(stderr, "input = %s\n", g_enum[info_lexer->input]);
		fprintf(stderr, "output = %s\n", g_enum[info_lexer->output]);
		fprintf(stderr, "delim = %s\n", info_lexer->delim);
		fprintf(stderr, "---------------------------");
		fprintf(stderr, "\n");
		info_lexer = info_lexer->next;
	}
	fprintf(stderr, "\033[0m");
	return ;
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
			line = readline("\033[0;37m \033[1m MINIHELL_\033[0m> ");
		else
			line = readline("\033[0;31m \033[1m Ç̈ͮ̾ͫ̆ͯ̏U̷͂̎Rͩ̀S̶̽ͮ̑̋̉ͩ̃Ë̷́̓̾͆ͫḐ͒̆̚̚_\033[0m> ");
		if (line == NULL)
		{
			free(line);
			terminate = 1;
		}
		else if (line[0] != '\0')
		{
			add_history(line);
			shell->cmd_lst = lexing(line);
			if (!shell->cmd_lst)
				exit(1); //should display an error
			printing_lexer(shell->cmd_lst);
			if (!shell->cmd_lst->next && is_builtin(shell) != -1)
				execute_builtin(shell);
			else
				g_exit_status = execute_cmds(shell->cmd_lst, shell->env_cpy);
			free_ll(&shell->cmd_lst);
		}
		else
			free(line);
	}
}

t_minishell	init_minishell(int argc, char *argv[], char *envp[])
{
	t_minishell shell;

	argv[0] = NULL;
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
