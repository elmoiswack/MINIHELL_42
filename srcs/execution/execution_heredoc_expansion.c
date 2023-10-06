#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*expand_heredoc_var(char *heredoc_line, int var_index, char *env_cpy[])
{
	char	*temp;
	char	*string_before_var;
	char	*string_after_var;
	int		start;

	start = var_index;
	var_index++;
	while (heredoc_line[var_index] && heredoc_line[var_index] != ' '
		&& heredoc_line[var_index] != '$' && heredoc_line[var_index] != '"'
		&& heredoc_line[var_index] != 39)
		var_index++;
	temp = ft_substr(heredoc_line, start, var_index - start);
	if (!var_exists(env_cpy, temp))
		return (heredoc_line);
	else
	{
		string_before_var = ft_substr(heredoc_line, 0, start);
		string_after_var = ft_substr(heredoc_line, var_index,
				ft_strlen(heredoc_line + var_index));
		temp = ft_getenv(temp + 1, env_cpy);
		heredoc_line = ft_strjoin_and_free(string_before_var, temp);
		heredoc_line = ft_strjoin_and_free(heredoc_line, string_after_var);
		free(string_after_var);
		return (free(temp), heredoc_line);
	}
}

char	*expand_heredoc_pid(char *heredoc_line, int pid_token_index)
{
	char	*string_before_pid;
	char	*string_after_pid;
	char	*pid_str;
	int		pid_int;

	pid_int = (int)getpid();
	pid_str = ft_itoa(pid_int);
	if (pid_token_index > 0)
	{
		string_before_pid = ft_substr(heredoc_line, 0, pid_token_index);
		string_after_pid = ft_substr(heredoc_line, pid_token_index + 2,
				ft_strlen(heredoc_line));
		string_after_pid = ft_strjoin_and_free(pid_str, string_after_pid);
		free(heredoc_line);
		heredoc_line = ft_strjoin_and_free(string_before_pid, string_after_pid);
		free(string_after_pid);
		return (heredoc_line);
	}
	else
		heredoc_line = ft_strjoin_and_free(pid_str,
				heredoc_line + pid_token_index + 2);
	return (heredoc_line);
}
