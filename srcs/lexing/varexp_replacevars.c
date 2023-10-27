/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_replacevars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:48:58 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/27 16:52:48 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	rplc_vars_loop_cpy(char *line, \
	char *new_line, int *index_new, int *index)
{
	if (line[*index] == '\0')
		return ;
	new_line[*index_new] = line[*index];
	*index_new += 1;
	*index += 1;
}

char	*replace_vars_loop(char *line, char *new_line, \
	char **env_temp, int index)
{
	int	index_new;
	int	index_env;

	index_new = 0;
	index_env = 0;
	while (line[index])
	{
		if ((line[index] == '$') \
			&& (line[index + 1] != '\0' && line[index + 1] != '$' \
				&& line[index + 1] != '"' && line[index + 1] != '\''))
		{
			while ((line[index] == '$') \
				&& (line[index + 1] != '\0' && line[index + 1] != '$'))
			{
				index = get_env_end(line, index + 1);
				new_line = put_env_in_line(new_line, index_new, \
					env_temp, index_env);
				index_new += ft_strlen(env_temp[index_env]);
				index_env++;
			}
		}
		rplc_vars_loop_cpy(line, new_line, &index_new, &index);
	}
	return (new_line);
}

char	*replace_variables(char *line, char **env_temp)
{
	char	*new_line;
	int		index;

	index = 0;
	new_line = ft_calloc(get_size_strings(line, env_temp) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	new_line = replace_vars_loop(line, new_line, env_temp, index);
	free(line);
	return (new_line);
}
