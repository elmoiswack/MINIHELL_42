/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/10 14:15:32 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*replace_expanded_variable(char *word_var, char *exp_var, int start)
{
	char	*new_line;
	int		index;
	int		index_word;

	new_line = ft_calloc(ft_strlen(word_var) + \
		ft_strlen(exp_var) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	index = 0;
	index_word = 0;
	while (index_word < start)
	{
		new_line[index] = word_var[index_word];
		index++;
		index_word++;
	}
	new_line = finish_new_line(new_line, exp_var, word_var, index);
	free(word_var);
	free(exp_var);
	return (new_line);
}

char	*expand_variable(char *word_var, int *index, char **env_cpy)
{
	int		end;
	char	*exp_var;

	end = *index;
	end++;
	while (word_var[end] && (ft_isalpha(word_var[end]) || word_var[end] == '_'))
		end++;
	exp_var = ft_calloc(end - *index + 1, sizeof(char));
	if (!exp_var)
		return (NULL);
	exp_var = get_variable_string(word_var, exp_var, *index, end);
	exp_var = remove_dollar_sign(exp_var);
	if (!exp_var)
		return (NULL);
	exp_var = get_expanded_variable(exp_var, env_cpy);
	if (!exp_var)
	{
		exp_var = ft_calloc(1, sizeof(char));
		if (!exp_var)
			return (NULL);
	}
	word_var = replace_expanded_variable(word_var, exp_var, *index);
	return (word_var);
}

char	*envexp_loop_other(char *word_var, \
	int *index, char **env_cpy, t_lexer *info_list)
{
	int	i;

	i = *index;
	if (word_var[i] == '$' \
		&& word_var[i + 1] && ft_isalpha(word_var[i + 1]))
	{
		word_var = expand_variable(word_var, &i, env_cpy);
		if (!word_var)
			return (NULL);
	}
	if (word_var[i] == '$' \
		&& word_var[i + 1] && word_var[i + 1] == '?')
	{
		word_var = expand_exit_status(word_var, info_list);
		if (!word_var)
			return (NULL);
		i += 2;
	}
	*index = i;
	return (word_var);
}

char	*env_expander_loop(char *word_var, \
	char **env_cpy, int index, t_lexer *info_list)
{
	int	check;

	check = 1;
	while (word_var[index])
	{
		if (word_var[index] == '"')
			check = check * -1;
		if (check > 0 && word_var[index] == '\'')
		{
			index++;
			while (word_var[index] != '\'')
				index++;
			if (word_var[index] == '\0')
				return (word_var);
		}
		word_var = envexp_loop_other(word_var, \
			&index, env_cpy, info_list);
		index++;
	}
	return (word_var);
}

char	**replace_var_expander(t_lexer *info_list, char **splitted_line, \
	char **env_cpy, int *enum_array)
{
	int	index;

	index = 0;
	while (splitted_line[index])
	{
		if (enum_array[index] != DELIMITER)
		{
			splitted_line[index] = \
				env_expander_loop(splitted_line[index], env_cpy, 0, info_list);
			if (!splitted_line[index])
			{
				free_double_array(splitted_line);
				error_lex(info_list, 1, "");
				return (NULL);
			}
		}
		index++;
	}
	return (splitted_line);
}
