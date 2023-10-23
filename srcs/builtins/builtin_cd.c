/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_cd.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:20:27 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 21:42:52 by flip          ########   odam.nl         */
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

static int	chdir_oldpwd(char *env_cpy[], t_minishell *shell)
{
	char	*value;

	value = ft_getenv("OLDPWD", env_cpy);
	ft_printf("value: %s\n", value);
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

int	execute_cd(t_minishell *shell)
{
	int		arg_len;

	if (!shell->cmd_lst->content[1])
		return (chdir(getenv("HOME")), update_pwd(shell), 0);
	arg_len = ft_strlen(shell->cmd_lst->content[1]);
	if (is_relative_path(shell->cmd_lst->content[1]))
		return(update_old_pwd(shell), chdir(shell->cmd_lst->content[1]));
	else if (ft_strncmp(shell->cmd_lst->content[1], "-", arg_len) == 0)
		return (chdir_oldpwd(shell->env_cpy, shell));
	else if (ft_strncmp(shell->cmd_lst->content[1], "~", arg_len) == 0)
		return (chdir_home(shell->cmd_lst->content, shell->env_cpy, shell));
	else if (chdir(shell->cmd_lst->content[1]) == -1)
		return (perror("cd"), 1);
	return (update_pwd(shell), 0);
}
