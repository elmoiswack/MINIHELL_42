#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	printing_lexer(t_lexer *info_lexer)
{
	int	index;
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
		printf("if there is a pipe input = %i\n", info_lexer->input);
		printf("if there is a pipe output = %i\n", info_lexer->output);
		printf("delim = %s\n", info_lexer->delim);
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