#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	execute_echo(char **raw_input, int *exit_status)
{
	char	*value;

	value = NULL;
	if (!raw_input[1])
		ft_printf("\n");
	else if (ft_strncmp(raw_input[1], "$$", 2) == 0)
		ft_printf("%d\n", (int)getpid());
	else if (ft_strncmp(raw_input[1], "$?", 2) == 0)
		ft_printf("%d\n", *exit_status);
	else if (arg_is_env(raw_input[1], &value) == 1)
		ft_printf("%s\n", value);
	else
		print_double_array(raw_input);
	*exit_status = 0;
}

void	update_pwd(t_minishell *shell)
{
	int		index;
	char	cwd[256];
	char	*new_pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd()");
		shell->status = 1;
		return ;
	} 
	index = var_exists(shell->env_cpy, "PWD", 3);
	if (index == -1)
		return ;
	else
	{
		new_pwd = ft_strjoin("PWD=", cwd);		
		shell->env_cpy = replace_str_in_array(shell->env_cpy, new_pwd, index);
	}
}

void	update_old_pwd(t_minishell *shell)
{
	int		index;
	char	cwd[256];
	char	*new_pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd()");
		shell->status = 1;
		return ;
	} 
	index = var_exists(shell->env_cpy, "OLDPWD", 6);
	if (index == -1)
		return ;
	else
	{
		new_pwd = ft_strjoin("OLDPWD=", cwd);		
		shell->env_cpy = replace_str_in_array(shell->env_cpy, new_pwd, index);
	}
}

void	execute_cd(t_minishell *shell)
{
	int	arg_len;

	update_old_pwd(shell);	
	if (shell->cmd_lst->content[1])
		arg_len = ft_strlen(shell->cmd_lst->content[1]);
	if (!shell->cmd_lst->content[1])
		chdir(getenv("HOME"));
	else if (ft_strncmp(shell->cmd_lst->content[1], "..", arg_len) == 0 || ft_strncmp(shell->cmd_lst->content[1], "../", arg_len) == 0)
		chdir("../");
	else if (chdir(shell->cmd_lst->content[1]) == -1)
	{
		shell->status = 1;
		return (perror("cd"));
	}
	update_pwd(shell);
	shell->status = 0;
}
		
void	execute_pwd(int *exit_status)
{
	char	cwd[256];
	int	cd_len;
	int	total_len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd()");
		*exit_status = 1;
		return ;
	}
	else
	{
		cd_len = ft_strlen(ft_strrchr(cwd, '/'));
		total_len = ft_strlen(cwd);
		write(1, cwd, total_len - cd_len);
		write(1, "\033[0;31m", 8);
		write(1, ft_strrchr(cwd, '/'), ft_strlen(ft_strrchr(cwd, '/')));
		write(1, "\033[0m\n", 6);
		*exit_status = 0;
		return ;
	}
}

void	execute_env(char *envp[])
{
	print_double_array(envp);
}

void	execute_export(t_minishell *shell)
{
	char	*var;
	int		eq_index;
	int		replace_index;

	if (!shell->cmd_lst->content[1])
		return (execute_env(shell->env_cpy));
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

void	execute_unset(t_minishell *shell)
{
	int	var_index;

	var_index = 0;
	if (shell->cmd_lst->content[1] == NULL)
	{
		shell->status = -1;
		return (error_unset_too_few_args());
	}
	var_index = var_exists(shell->env_cpy, shell->cmd_lst->content[1], ft_strlen(shell->cmd_lst->content[1]));
	if (var_index >= 0)
		shell->env_cpy = remove_str_from_array(shell->env_cpy, var_index);
}
