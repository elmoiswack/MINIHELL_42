// Global array - used to print out the enum strings. Must be deleted before handing in the project.
#include "../../includes/minishell.h"
#include <stdio.h>

static const char *g_enum[] = {
[PIPE_READ] = "READ", //0
[PIPE_WRITE] = "WRITE", //1
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
[HEREDOC] = "HEREDOC", //16
};

static const char *g_builtin[] = {
	[ECHO] = "ECHO",
	[CD] = "CD",
	[PWD] = "PWD",
	[ENV] = "ENV",
	[EXIT] = "EXIT",
	[EXPORT] = "EXPORT",
	[UNSET] = "UNSET",
	[NO_BUILTIN] = "NO_BUILTIN",
};

void	print_cmd_lst(t_lexer *head)
{
	t_lexer	*current;
	int		n;
	t_builtin builtin;

	current = head;
	n = 0;
	fprintf(stderr, "\033[0;36m--------EXECUTIONER--------\n");
	fprintf(stderr, "PROCESS\tCMD\tINPUT\tOUTPUT\tFILE\tBUILTIN\n");
	while (current)
	{
		builtin = is_builtin(current);
		fprintf(stderr, "%d\t%s\t%s\t%s\t%s\t%s\n", n, current->content[0], g_enum[current->input], g_enum[current->output], current->file, g_builtin[builtin]);
		n++;
		current = current->next;
	}
	fprintf(stderr, "---------------------------\033[0m\n");
}

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
		int i = 0;
		if (info_lexer->delim)
		{
			while (info_lexer->delim[i])
			{
				fprintf(stderr, "delim[%i] = %s\n", i, info_lexer->delim[i]);
				i++;
			}
		}
		fprintf(stderr, "---------------------------");
		fprintf(stderr, "\n");
		info_lexer = info_lexer->next;
	}
	fprintf(stderr, "\033[0m");
	return ;
}

