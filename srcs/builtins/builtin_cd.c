#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	update_pwd(t_minishell *shell)
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
	index = var_exists(shell->env_cpy, "PWD");
	if (index == -1)
		return ;
	else
	{
		new_pwd = ft_strjoin("PWD=", cwd);
		shell->env_cpy = replace_str_in_array(shell->env_cpy, new_pwd, index);
		free(new_pwd);
	}
}

static void	update_old_pwd(t_minishell *shell)
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
	index = var_exists(shell->env_cpy, "OLDPWD");
	if (index == -1)
		return ;
	else
	{
		new_pwd = ft_strjoin("OLDPWD=", cwd);
		shell->env_cpy = replace_str_in_array(shell->env_cpy, new_pwd, index);
		free(new_pwd);
	}
}

static void	chdir_oldpwd(char *env_cpy[], t_minishell *shell)
{
	char	*value;

	value = ft_getenv("OLDPWD", env_cpy);
	ft_printf("value: %s\n", value);
	update_old_pwd(shell);
	if (chdir(value) == -1)
	{
		free(value);
		return (g_exit_status = 1, perror("OLDPWD"));
	}
	free(value);
}

static void	chdir_home(char *content[], char *env_cpy[], t_minishell *shell)
{
	char	*value;

	if (content[1][0] == '~' && content[1][1] == '/')
	{
		value = ft_strjoin(ft_getenv("HOME", env_cpy), ft_strchr(content[1], '/'));
		update_old_pwd(shell);
		if (chdir(value) == -1)
		{
			free(value);
			return (g_exit_status = 1, perror("~"));
		}
	}
	else
	{
		value = ft_getenv("HOME", env_cpy);
		update_old_pwd(shell);
		if (chdir(value) == -1)
		{
			free(value);
			return (g_exit_status = 1, perror("~"));
		}
	}
	free(value);
}

static bool	is_relative_path(char *content)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (content[i] && content[j])
	{
		if (ft_strncmp(&content[i], "../", 3) == 0)
		{
			i+=3;
			continue;
		}
		else
		{
			ft_printf("False\n");
			return (false);
		}
		j++;
	}
	ft_printf("True\n");
	return (true);
}

void	execute_cd(t_minishell *shell)
{
	int		arg_len;

	if (!shell->cmd_lst->content[1])
		return (chdir(getenv("HOME")), update_pwd(shell));
	arg_len = ft_strlen(shell->cmd_lst->content[1]);
	if (is_relative_path(shell->cmd_lst->content[1]))
	{
		update_old_pwd(shell);
		chdir(shell->cmd_lst->content[1]);
	}
	else if (ft_strncmp(shell->cmd_lst->content[1], "-", arg_len) == 0)
		chdir_oldpwd(shell->env_cpy, shell);
	else if (ft_strncmp(shell->cmd_lst->content[1], "~", arg_len) == 0)
		chdir_home(shell->cmd_lst->content, shell->env_cpy, shell);
	else if (chdir(shell->cmd_lst->content[1]) == -1)
		return (g_exit_status = 1, perror("cd"));
	return (g_exit_status = 0, update_pwd(shell));
}
