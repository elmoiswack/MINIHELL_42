#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static char	*expand_value(char *content, char *var, char *env_cpy[])
{
	int		eq_index;
	char	*value;
	char	*expand;

	eq_index = ft_strchr_index(content, '=');
	value = ft_substr(content, eq_index + 1, ft_strlen(content + eq_index));
	if (var_exists(env_cpy, value) == -1)
		return (content);
	var = ft_substr(content, 0, eq_index + 1);
	expand = ft_strjoin(var, ft_getenv(value, env_cpy));
	return (expand);
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
	replace_index = var_exists(shell->env_cpy, var);
	shell->cmd_lst->content[1] = expand_value(shell->cmd_lst->content[1], var, shell->env_cpy);
	if (ft_strchr(shell->cmd_lst->content[1], '=') == NULL && ft_strisalpha(shell->cmd_lst->content[1]) == 0)
	{
		g_exit_status = -1;
		return (error_export_invalid_identifier(shell->cmd_lst->content[1]));
	}
	else if (replace_index >= 0)
		shell->env_cpy = replace_str_in_array(shell->env_cpy, shell->cmd_lst->content[1], replace_index);
	else
		shell->env_cpy = append_to_double_array(shell->env_cpy, shell->cmd_lst->content[1]);
}

