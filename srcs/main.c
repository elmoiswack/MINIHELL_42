#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//Global array, used to print out the enum strings. Must be deleted before handing in the project.
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
[STDIN_IN] = "STDIN_IN", //14
[STDOUT_OUT] = "STDOUT_OUT", //15
};

void	printing_lexer(t_lexer *info_lexer)
{
	int	index;

	fprintf(stderr, "----------PARSER-----------");
	while(info_lexer)
	{
		fprintf(stderr, "\n");
		index = 0;
		while (info_lexer->content[index])
		{
			fprintf(stderr, "info_lexer->content = %s\n", info_lexer->content[index]);
			index++;
		}
		fprintf(stderr, "content path = %s\n", info_lexer->path);
		fprintf(stderr, "file name = %s\n", info_lexer->file);
		fprintf(stderr, "if there is a pipe input = [%i] %s\n", info_lexer->input, g_enum[info_lexer->input]);
		fprintf(stderr, "if there is a pipe output = [%i] %s\n", info_lexer->output, g_enum[info_lexer->output]);
		fprintf(stderr, "delim = %s\n", info_lexer->delim);
		fprintf(stderr, "---------------------------");
		fprintf(stderr, "\n");
		info_lexer = info_lexer->next;
	}
	return ;
}

void	display_prompt(t_minishell *shell)
{	
	char	*line;

	init_ascii_art();
	while (1)
	{
		if (shell->status == 0)	
			line = readline("\033[0;37m \033[1m MINIHELL_\033[0m> ");
		else
			line = readline("\033[0;31m \033[1m Ç̈ͮ̾ͫ̆ͯ̏U̷͂̎Rͩ̀S̶̽ͮ̑̋̉ͩ̃Ë̷́̓̾͆ͫḐ͒̆̚̚_\033[0m> ");
		add_history(line);
		shell->cmd_lst = lexing(line);
		if (!shell->cmd_lst)
			exit(1);
		printing_lexer(shell->cmd_lst);
		if (!shell->cmd_lst->next && is_builtin(shell) != -1)
			shell->status = execute_builtin(shell);
		else
			shell->status = execute_cmds(shell->cmd_lst, shell->env_cpy);
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

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	shell;

	shell = init_minishell(argc, argv, envp);
	display_prompt(&shell);
	return (0);
}
