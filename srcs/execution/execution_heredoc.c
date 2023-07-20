#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void	change_permission_heredoc_tmp()
{
	char	*args[] = {"chmod", "777", "./data/heredoc.tmp", NULL};
	int		status;
	pid_t	pid;
	// int		hd_fd;
	
	// if ((hd_fd = open("./data/heredoc.tmp", O_EXCL | O_RDWR)) < 0)
	// 	return ;
	pid = fork();
	if (pid == 0 && execve(get_path("chmod"), args, NULL) < 0)
		exit(-1);
	waitpid(pid, &status, 0);
}

void	create_heredoc_tmp(char *delim)
{
	char	*heredoc_line;
	int		heredoc_tmp;

	change_permission_heredoc_tmp();
	heredoc_tmp = open("./data/heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_tmp < 0)
		return (perror("heredoc_tmp"));
	heredoc_line = readline("> ");
	while (heredoc_line != NULL && !(ft_strncmp(heredoc_line, delim, ft_strlen(delim)) == 0))
	{
		
		write(heredoc_tmp, heredoc_line, ft_strlen(heredoc_line));
		write(heredoc_tmp, "\n", 1);
		if (heredoc_line)
			free(heredoc_line);
		heredoc_line = readline("> ");
	}
	close(heredoc_tmp);
}

void	clean_tmp_files(char *envp[])
{
	char	*args[] = {"rm", "./data/heredoc.tmp", NULL};
	pid_t	pid;
	
	pid = fork();
	if (pid == 0 && execve(get_path("rm"), args, envp) < 0)
	{
		perror("error cleanup tmp");
		exit(-1);
	}
}

