#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

const static char *g_enum[] = {
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

	printf("----------PARSER-----------");
	while(info_lexer)
	{
		printf("\n");
		index = 0;
		while (info_lexer->content[index])
		{
			printf("info_lexer->content = %s\n", info_lexer->content[index]);
			index++;
		}
		printf("content path = %s\n", info_lexer->path);
		printf("file name = %s\n", info_lexer->file);
		printf("if there is a pipe input = [%i] %s\n", info_lexer->input, g_enum[info_lexer->input]);
		printf("if there is a pipe output = [%i] %s\n", info_lexer->output, g_enum[info_lexer->output]);
		printf("delim = %s\n", info_lexer->delim);
		printf("---------------------------");
		printf("\n");
		info_lexer = info_lexer->next;
	}
	return ;
}

void	display_prompt(char *envp[])
{	
	char	*line;
	t_lexer *info_lexer;
	int		builtin;
	int		status;

	builtin = 0;
	status = 0;
	init_ascii_art();
	while (1)
	{
		if (status == 0)	
			line = readline("\033[0;37m \033[1m MINIHELL_\033[0m> ");
		else
			line = readline("\033[0;31m \033[1m Ç̈ͮ̾ͫ̆ͯ̏U̷͂̎Rͩ̀S̶̽ͮ̑̋̉ͩ̃Ë̷́̓̾͆ͫḐ͒̆̚̚\033[0m> ");
		add_history(line);
		info_lexer = lexing(line);
		if (!info_lexer)
			exit(1);
		printing_lexer(info_lexer);
		if (!info_lexer->next && is_builtin(info_lexer->content, &builtin) != -1)
			execute_builtin(info_lexer->content, envp, builtin, &status);
		else
			status = execute_cmds(info_lexer, envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
		exit(1);
	argv = NULL;
	display_prompt(envp);
	return (0);
}