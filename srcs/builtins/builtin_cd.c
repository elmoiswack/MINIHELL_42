/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_cd.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:20:27 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/17 12:10:29 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
		return (perror("getcwd()"));
	if (var_exists(shell->env_cpy, "PWD") == -1)
	{
		new_pwd = ft_strjoin("PWD=", cwd);
		add_env(shell, new_pwd);
		free(new_pwd);
		return ;
	}
	index = var_exists(shell->env_cpy, "PWD");
	if (index == -1)
		return ;
	else
	{
		new_pwd = ft_strjoin("PWD=", cwd);
		if (!new_pwd)
			return ;
		shell->env_cpy = ft_replace_str_in_array(shell->env_cpy,
				new_pwd, index);
		free(new_pwd);
	}
}

static void	update_old_pwd(t_minishell *shell)
{
	int		index;
	char	*temp;
	char	*new_pwd;

	if (var_exists(shell->env_cpy, "OLDPWD") == -1)
		add_env(shell, "OLDPWD=");
	temp = ft_getenv("PWD", shell->env_cpy);
	if (!temp)
		return ;
	index = var_exists(shell->env_cpy, "OLDPWD");
	if (index == -1)
		return ;
	else
	{
		new_pwd = ft_strjoin("OLDPWD=", temp);
		if (!new_pwd)
			return (free(temp));
		shell->env_cpy = ft_replace_str_in_array(shell->env_cpy,
				new_pwd, index);
		free(new_pwd);
		free(temp);
	}
}

static int	chdir_oldpwd(char *env_cpy[], t_minishell *shell)
{
	char	*value;

	value = ft_getenv("OLDPWD", env_cpy);
	if (!value)
		return (1);
	update_old_pwd(shell);
	if (chdir(value) == -1)
	{
		free(value);
		return (perror("OLDPWD"), 1);
	}
	free(value);
	return (0);
}

static int	chdir_home(char *content[], char *env_cpy[], t_minishell *shell)
{
	char	*value;

	if (content[1][0] == '~' && content[1][1] == '/')
	{
		value = ft_strjoin(ft_getenv("HOME", env_cpy),
				ft_strchr(content[1], '/'));
		update_old_pwd(shell);
		if (chdir(value) == -1)
		{
			free(value);
			return (perror("~"), 1);
		}
	}
	else
	{
		value = ft_getenv("HOME", env_cpy);
		update_old_pwd(shell);
		if (chdir(value) == -1)
		{
			free(value);
			return (perror("~"), 1);
		}
	}
	free(value);
	return (0);
}

int	execute_cd(t_minishell *shell, t_lexer *node, int err)
{
	int		arg_len;

	err = 0;
	if (!shell->cmd_lst->content[1])
		return (go_to_home(shell->env_cpy), update_pwd(shell), 0);
	if (ft_arrlen(node->content) >= 3)
		return (err_log(E_ERR, "cd: too many arguments"), 1);
	arg_len = ft_strlen(shell->cmd_lst->content[1]);
	if (is_relative_path(shell->cmd_lst->content[1]))
	{
		update_old_pwd(shell);
		err = chdir(shell->cmd_lst->content[1]);
	}
	else if (ft_strncmp(shell->cmd_lst->content[1], "-", arg_len) == 0)
		err = chdir_oldpwd(shell->env_cpy, shell);
	else if (ft_strncmp(shell->cmd_lst->content[1], "~", arg_len) == 0)
		err = chdir_home(shell->cmd_lst->content, shell->env_cpy, shell);
	else
	{
		update_old_pwd(shell);
		err = chdir(shell->cmd_lst->content[1]);
	}
	if (err < 0)
		perror("cd");
	return (update_pwd(shell), err);
}
