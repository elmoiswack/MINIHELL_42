#include "../../includes/minishell.h"
#include "../../libft/libft.h"
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
	index = var_exists(shell->env_cpy, "PWD", 3);
	if (index == -1)
		return ;
	else
	{
		new_pwd = ft_strjoin("PWD=", cwd);		
		shell->env_cpy = replace_str_in_array(shell->env_cpy, new_pwd, index);
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
	char *value;

	update_old_pwd(shell);	
	if (!shell->cmd_lst->content[1])
	{
		chdir(getenv("HOME"));
		update_pwd(shell);
		return ;
	}
	arg_len = ft_strlen(shell->cmd_lst->content[1]);
	if (ft_strncmp(shell->cmd_lst->content[1], "..", arg_len) == 0 || ft_strncmp(shell->cmd_lst->content[1], "../", arg_len) == 0)
		chdir("../");
	else if (ft_strncmp(shell->cmd_lst->content[1], "-", arg_len) == 0)
	{
		value = getenv("OLDPWD");
		if (chdir(value) == -1)
		{
			g_exit_status = 1;
			return (perror("OLDPWD"));
		}
	}
	else if (ft_strncmp(shell->cmd_lst->content[1], "~", arg_len) == 0)
	{
		value = getenv("HOME");
		if (chdir(value) == -1)
		{
			g_exit_status = 1;
			return (perror("~"));
		}
	}
	else if (shell->cmd_lst->content[1][0] == '~' && shell->cmd_lst->content[1][1] == '/')
	{
		value = ft_strjoin(getenv("HOME"), ft_strchr(shell->cmd_lst->content[1], '/'));
		if (chdir(value) == -1)
		{
			g_exit_status = 1;
			return (perror("~"));
		}
	}
	else if (chdir(shell->cmd_lst->content[1]) == -1)
	{
		g_exit_status = 1;
		return (perror("cd"));
	}
	update_pwd(shell);
	g_exit_status = 0;
}
