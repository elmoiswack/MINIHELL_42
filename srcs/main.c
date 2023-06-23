#include "../includes/minishell.h"
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

int	main(void)
{
	char 	*line;
	t_lexer *info_lexer;
	
	while (1)
	{
		line = readline("Minishell > ");
		add_history(line);
		info_lexer = lexing(line);
		if (!info_lexer)
		{
			printf("nani da fuq\n");
			exit(1);
		}
		printing_lexer(info_lexer);
	}
	return (0);
}
//kdasdas