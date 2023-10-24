/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_export.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:15:31 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/24 12:45:49 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static char	*expand_value(char *content, char *var, char *env_cpy[])
{
	int		eq_index;
	char	*value;
	char	*expand;
	char	*env_temp;

	eq_index = ft_strchr_index(content, '=');
	value = ft_substr(content, eq_index + 1, ft_strlen(content + eq_index));
	if (var_exists(env_cpy, value) == -1)
		return (free(value), content);
	var = ft_substr(content, 0, eq_index + 1);
	env_temp = ft_getenv(value, env_cpy);
	expand = ft_strjoin_and_free(var, env_temp);
	free(env_temp);
	free(value);
	return (free(content), expand);
}

static int	export_content(char *content, t_minishell *shell)
{
	char	*var;
	int		eq_index;
	int		replace_index;

	eq_index = ft_strchr_index(content, '=');
	var = ft_substr(content, 0, eq_index);
	replace_index = var_exists(shell->env_cpy, var);
	content = expand_value(content, var, shell->env_cpy);
	free(var);
	if (ft_strchr(content, '=') == NULL && ft_strisalpha(content) == 0)
		return (error_export_invalid_identifier(content), 1);
	else if (replace_index >= 0)
		shell->env_cpy = replace_str_in_array(shell->env_cpy,
				content, replace_index);
	else
		shell->env_cpy = append_to_double_array(shell->env_cpy, content);
	return (0);
}

int	execute_export(t_minishell *shell)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (!shell->cmd_lst->content[i])
		return (execute_env(shell->env_cpy));
	while (shell->cmd_lst->content[i] && err != 1)
	{
		err = export_content(shell->cmd_lst->content[i], shell);
		i++;
	}
	return (err);
}
