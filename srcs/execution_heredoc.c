#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdlib.h>

void	create_heredoc_tmp(char *delim)
{
	char	*heredoc_line;
	int		heredoc_tmp;

	heredoc_tmp = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_tmp < 0)
		exit(-1);
	heredoc_line = readline("> ");
	while (!(ft_strncmp(heredoc_line, delim, ft_strlen(delim)) == 0))
	{
		write(heredoc_tmp, heredoc_line, ft_strlen(heredoc_line));
		write(heredoc_tmp, "\n", 1);
		if (heredoc_line)
			free(heredoc_line);
		heredoc_line = readline("> ");
	}
}
