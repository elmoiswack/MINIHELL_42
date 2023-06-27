#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	execute_echo(char **raw_input, int *exit_status)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	if (ft_strncmp(raw_input[1], "$$", 2) == 0)
		ft_printf("%d\n", (int)getpid());
	else if (ft_strncmp(raw_input[1], "$?", 2) == 0)
		ft_printf("%d\n", *exit_status);
	else if (arg_is_env(raw_input[1], &value) == 1)
		ft_printf("%s\n", value);
	else
	{
		while (raw_input[i++])
		{
			if (raw_input[i])
				ft_printf("%s ", raw_input[i]);
		}
		ft_printf("\n");
	}
}

void	execute_cd(char **raw_input, int *exit_status)
{
	int	arg_len;
	
	if (raw_input[1])
		arg_len = ft_strlen(raw_input[1]);
	if (!raw_input[1])
		chdir(getenv("HOME"));
	else if (ft_strncmp(raw_input[1], "..", arg_len) == 0 || ft_strncmp(raw_input[1], "../", arg_len) == 0)
		chdir("../");
	else if (chdir(raw_input[1]) == -1)
	{
		perror("cd");
		*exit_status = 1;
	}
}
		
void	execute_pwd()
{
	char	cwd[256];
	int	cd_len;
	int	total_len;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd()");
	else
	{
		cd_len = ft_strlen(ft_strrchr(cwd, '/'));
		total_len = ft_strlen(cwd);
		write(1, cwd, total_len - cd_len);
		write(1, "\033[0;31m", 8);
		write(1, ft_strrchr(cwd, '/'), ft_strlen(ft_strrchr(cwd, '/')));
		write(1, "\033[0m\n", 6);
	}
}

void	execute_env(char *envp[])
{
	print_double_array(envp);
}

int	var_exists(char	**env, char *var, int var_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

//		[] export lol=jo

void	execute_export(t_minishell *shell)
{
	char	*var;
	int		eq_index;
	int		replace_index;

	if (shell->cmd_lst->content[1] == NULL)
		execute_env(shell->env_cpy);
	eq_index = ft_strchr_index(shell->cmd_lst->content[1], '=');
	var = ft_substr(shell->cmd_lst->content[1], 0, eq_index);
	replace_index = var_exists(shell->env_cpy, var, eq_index);
	if (ft_strchr(shell->cmd_lst->content[1], '=') == NULL && ft_strisalpha(shell->cmd_lst->content[1]) == 0)
	{
		shell->status = -1;
		return (error_export_invalid_identifier(shell->cmd_lst->content[1]));
	}
	else if (replace_index >= 0)
		shell->env_cpy = replace_str_in_array(shell->env_cpy, shell->cmd_lst->content[1], replace_index);
	else
		shell->env_cpy = append_to_double_array(shell->env_cpy, shell->cmd_lst->content[1]);
}
