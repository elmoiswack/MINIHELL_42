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

static void	chdir_oldpwd(void)
{
	char	*value;

	value = getenv("OLDPWD");
	if (chdir(value) == -1)
		return (g_exit_status = 1, perror("OLDPWD"));
}

static void	chdir_home(char *content[])
{
	char	*value;

	if (content[1][0] == '~' && content[1][1] == '/')
	{
		value = ft_strjoin(getenv("HOME"), ft_strchr(content[1], '/'));
		if (chdir(value) == -1)
			return (g_exit_status = 1, perror("~"));
	}
	else
	{
		value = getenv("HOME");
		if (chdir(value) == -1)
			return (g_exit_status = 1, perror("~"));
	}
	free(value);
}

void	execute_cd(t_minishell *shell)
{
	int		arg_len;

	update_old_pwd(shell);
	if (!shell->cmd_lst->content[1])
		return (chdir(getenv("HOME")), update_pwd(shell));
	arg_len = ft_strlen(shell->cmd_lst->content[1]);
	if (ft_strncmp(shell->cmd_lst->content[1], "..", arg_len) == 0
		|| ft_strncmp(shell->cmd_lst->content[1], "../", arg_len) == 0)
		chdir("../");
	else if (ft_strncmp(shell->cmd_lst->content[1], "-", arg_len) == 0)
		chdir_oldpwd();
	else if (ft_strncmp(shell->cmd_lst->content[1], "~", arg_len) == 0)
		chdir_home(shell->cmd_lst->content);
	else if (chdir(shell->cmd_lst->content[1]) == -1)
		return (g_exit_status = 1, perror("cd"));
	return (g_exit_status = 0, update_pwd(shell));
}
