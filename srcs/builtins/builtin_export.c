/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_export.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:15:31 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/01 18:27:47 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

static char	*expand_value(char *content, char *var, char *env_cpy[])
{
	char	*value;
	char	*expand;
	char	*env_temp;
	int		eq_index;

	eq_index = ft_strchr_index(content, '=');
	value = ft_substr(content, eq_index + 1, ft_strlen(&content[eq_index + 1]));
	if (var_exists(env_cpy, value) == -1)
		return (free(value), content);
	var = ft_substr(content, 0, eq_index + 1);
	env_temp = ft_getenv(value, env_cpy);
	expand = ft_strjoin_and_free(var, env_temp);
	free(env_temp);
	free(value);
	return (free(content), expand);
}

static bool	valid_identifier(char *content)
{
	int	eq_index;

	eq_index = ft_strchr_index(content, '=');
	if ((ft_strchr(content, '=') == NULL && ft_strisalpha(content) == 0)
		|| (content[eq_index - 1] && content[eq_index - 1] != '+'
			&& ft_isalnum(content[eq_index - 1]) == 0))
		return (false);
	else
		return (true);
}

static char	*append_to_env(char *content, char *env_str)
{
	char	*value;
	int		eq_index;

	eq_index = ft_strchr_index(content, '=');
	value = ft_substr(content, eq_index + 1, ft_strlen(content + eq_index + 1));
	env_str = ft_strjoin_and_free(env_str, value);
	free (value);
	if (!env_str)
		return (content);
	return (env_str);
}

int	export_content(char *content, t_minishell *shell, bool append)
{
	char	*var;
	int		eq_index;
	int		replace_index;

	eq_index = ft_strchr_index(content, '=');
	if (content[eq_index - 1] == '+')
	{
		var = ft_substr(content, 0, eq_index - 1);
		ft_strlcpy(&content[eq_index - 1], &content[eq_index],
			ft_strlen(content));
		append = true;
	}
	else
		var = ft_substr(content, 0, eq_index);
	replace_index = var_exists(shell->env_cpy, var);
	if (replace_index >= 0 && append)
		return (free(var), shell->env_cpy[replace_index]
			= append_to_env(content, shell->env_cpy[replace_index]), 0);
	content = expand_value(content, var, shell->env_cpy);
	if (replace_index >= 0)
		shell->env_cpy = ft_replace_str_in_array(shell->env_cpy,
				content, replace_index);
	else
		shell->env_cpy = ft_append_to_double_array(shell->env_cpy, content);
	return (free(var), 0);
}

int	execute_export(t_minishell *shell, t_lexer *node)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (!node->content[1])
		return (print_double_array(shell->env_cpy), 0);
	while (node->content[i] && err != 1)
	{
		if (!ft_containschar(node->content[i], '='))
			return (err);
		else if (!valid_identifier(node->content[i]))
			return (err_log(E_IDENT, node->content[i]));
		err = export_content(node->content[i], shell, false);
		i++;
	}
	return (err);
}
