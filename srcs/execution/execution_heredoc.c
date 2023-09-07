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

	if (access("./data/heredoc.tmp", F_OK) == 0)
	{
		pid = fork();
		if (pid == 0 && execve(get_path("chmod"), args, NULL) < 0)
			exit(-1);
		waitpid(pid, &status, 0);
	}
}

char	*expand_heredoc_var(char *heredoc_line, int var_index, char *env_cpy[])
{
	char	*temp;
	char	*string_before_var;
	char	*string_after_var;
	int		start;

	start = var_index;
	var_index++;
	while (heredoc_line[var_index] && heredoc_line[var_index] != ' ' && heredoc_line[var_index] != '$')
		var_index++;
	temp = ft_substr(heredoc_line, start, var_index - start);
	ft_printf("temp: %s.\n", temp);
	if (!var_exists(env_cpy, temp, ft_strlen(temp)))
		return (heredoc_line);
	else 
	{
		string_before_var = ft_substr(heredoc_line, 0, start);
		ft_printf("str before var: %s\n", string_before_var);
		string_after_var = ft_substr(heredoc_line, var_index, ft_strlen(heredoc_line + var_index));
		ft_printf("str after var: %s\n", string_after_var);
		temp = ft_getenv(temp + 1, env_cpy);	
		ft_printf("temp (getenv): %s\n", temp);
		heredoc_line = ft_strjoin(string_before_var, temp);
		heredoc_line = ft_strjoin(heredoc_line, string_after_var);
		return (heredoc_line);
	}
}

char	*expand_heredoc_line(char *heredoc_line, char *env_cpy[])
{
	int	 i;
	
	i = 0;
	if (!heredoc_line)
		return (heredoc_line);
	while (heredoc_line[i])
	{
		if (heredoc_line[i] == '$' && heredoc_line[i + 1] != '\0' && ft_isalpha(heredoc_line[i + 1]) == 1)
			heredoc_line = expand_heredoc_var(heredoc_line, i, env_cpy);
		i++;
	}
	return (heredoc_line);
}

void	create_heredoc_tmp(char *delim, char *env_cpy[])
{
	char	*heredoc_line;
	int		heredoc_tmp;

	change_permission_heredoc_tmp();
	heredoc_tmp = open("./data/heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_tmp < 0)
		return (perror("heredoc_tmp"));
	heredoc_line = readline("> ");
	while (heredoc_line != NULL && !(ft_strncmp(heredoc_line, delim, (ft_strlen(delim) + ft_strlen(heredoc_line))) == 0))
	{
		heredoc_line = expand_heredoc_line(heredoc_line, env_cpy);
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

