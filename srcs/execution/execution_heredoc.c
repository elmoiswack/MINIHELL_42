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

static void	change_permission_heredoc_tmp(void)
{
	char	*args[4];
	int		status;
	pid_t	pid;

	args[0] = "chmod";
	args[1] = "777";
	args[2] = "./data/heredoc.tmp";
	args[3] = NULL;
	if (access("./data/heredoc.tmp", F_OK) == 0)
	{
		pid = fork();
		if (pid == 0 && execve(get_path(args[0]), args, NULL) < 0)
			exit(-1);
		waitpid(pid, &status, 0);
	}
}

static char	*expand_heredoc_line(char *heredoc_line, char *env_cpy[])
{
	int	i;

	i = 0;
	if (!heredoc_line)
		return (heredoc_line);
	while (heredoc_line[i])
	{
		if (heredoc_line[i] == '$' && heredoc_line[i + 1] != '\0'
			&& heredoc_line[i + 1] == '$')
		{
			heredoc_line = expand_heredoc_pid(heredoc_line, i);
			if (heredoc_line[i + 1])
				i++;
		}
		else if (heredoc_line[i] == '$' && heredoc_line[i + 1] != '\0'
			&& ft_isalpha(heredoc_line[i + 1]) == 1)
			heredoc_line = expand_heredoc_var(heredoc_line, i, env_cpy);
		i++;
	}
	return (heredoc_line);
}

static void	create_heredoc_tmp(char *delim, char *env_cpy[])
{
	char	*heredoc_line;
	int		heredoc_tmp;

	change_permission_heredoc_tmp();
	heredoc_tmp = open("./data/heredoc.tmp",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_tmp < 0)
		return (perror("heredoc_tmp"));
	heredoc_line = readline("> ");
	while (heredoc_line != NULL && !(ft_strncmp(heredoc_line, delim,
				(ft_strlen(delim) + ft_strlen(heredoc_line))) == 0))
	{
		heredoc_line = expand_heredoc_line(heredoc_line, env_cpy);
		write(heredoc_tmp, heredoc_line, ft_strlen(heredoc_line));
		write(heredoc_tmp, "\n", 1);
		if (heredoc_line)
			free(heredoc_line);
		heredoc_line = readline("> ");
	}
	free(heredoc_line);
	close(heredoc_tmp);
}

void	clean_tmp_files(t_lexer *head, char *envp[])
{
	char	*args[3];
	pid_t	pid;

	args[0] = "rm";
	args[1] = "./data/heredoc.tmp";
	args[2] = NULL;
	if (head->delim)
	{
		pid = fork();
		if (pid == 0 && execve(get_path(args[0]), args, envp) < 0)
		{
			perror("error cleanup tmp");
			exit(-1);
		}
	}
}

void	create_heredoc_loop(t_lexer *head, char *env_cpy[])
{
	t_lexer	*current;
	int		i;

	i = 0;
	current = head;
	if (current->delim)
	{
		while (current->delim[i])
		{
			create_heredoc_tmp(current->delim[i], env_cpy);
			i++;
		}
	}
}
