/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_expansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:39:33 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/10/27 15:04:55 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*expand_heredoc_var(char *heredoc_line,
		int var_index, char *env_cpy[])
{
	char	*temp;
	char	*string_before_var;
	char	*string_after_var;
	int		start;

	start = var_index;
	var_index++;
	while (heredoc_line[var_index] && heredoc_line[var_index] != ' '
		&& heredoc_line[var_index] != '$' && heredoc_line[var_index] != '"'
		&& heredoc_line[var_index] != 39)
		var_index++;
	temp = ft_substr(heredoc_line, start, var_index - start);
	if (!var_exists(env_cpy, temp))
		return (heredoc_line);
	else
	{
		string_before_var = ft_substr(heredoc_line, 0, start);
		string_after_var = ft_substr(heredoc_line, var_index,
				ft_strlen(heredoc_line + var_index));
		temp = ft_getenv(temp + 1, env_cpy);
		heredoc_line = ft_strjoin_and_free(string_before_var, temp);
		heredoc_line = ft_strjoin_and_free(heredoc_line, string_after_var);
		free(string_after_var);
		return (free(temp), heredoc_line);
	}
}

char	*expand_heredoc_line(char *heredoc_line, char *env_cpy[])
{
	int	i;

	i = 0;
	if (!heredoc_line)
		return (heredoc_line);
	while (heredoc_line[i])
	{
		if (heredoc_line[i] == '$' && heredoc_line[i + 1] != '\0'
			&& ft_isalpha(heredoc_line[i + 1]) == 1)
			heredoc_line = expand_heredoc_var(heredoc_line, i, env_cpy);
		i++;
	}
	return (heredoc_line);
}
