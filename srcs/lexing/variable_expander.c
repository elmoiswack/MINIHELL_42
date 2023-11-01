/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:47 by dhussain          #+#    #+#             */
/*   Updated: 2023/10/31 17:37:45 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*remove_quotes_string(char **splitted_line, int index)
{
	char	*new_line;
	int		index_l;
	int		index_x;

	index_l = 0;
	index_x = 0;
	new_line = ft_calloc(ft_strlen(splitted_line[index]) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	while (splitted_line[index][index_x])
	{
		if (splitted_line[index][index_x] != '"' && splitted_line[index][index_x] != '\'')
		{
			new_line[index_l] = splitted_line[index][index_x];
			index_l++;
		}
		index_x++;
	}
	free(splitted_line[index]);
	return (new_line);
}

int	check_for_envvar(char **splitted_line)
{
	int	index;
	int	index_x;

	index = 0;
	while (splitted_line[index])
	{
		index_x = 0;
		while (splitted_line[index][index_x])
		{
			if (splitted_line[index][index_x] == '$')
			{
				index_x++;
				if (splitted_line[index][index_x] == '\0')
					break ;
				if (ft_isalpha(splitted_line[index][index_x]) == 1)
					return (1);
			}
			index_x++;
		}
		index++;
	}
	return (-1);
}

char	*get_variable_string(char *word_var, char *exp_var, int begin, int end)
{
	int	index;

	index = 0;
	while (begin < end)
	{
		exp_var[index] = word_var[begin];
		index++;
		begin++;
	}
	return (exp_var);
}

char	*remove_dollar_sign(char *old)
{
	char	*new;
	int		index_n;
	int		index_o;
	
	new = ft_calloc(ft_strlen(old), sizeof(char));
	if (!new)
		return (NULL);
	index_n = 0;
	index_o = 0;
	while (old[index_o])
	{
		if (old[index_o] != '$')
		{
			new[index_n] = old[index_o];
			index_n++;
		}
		index_o++;
	}
	free(old);
	return (new);
}

char	*get_expanded_variable(char *exp_var, char **env_cpy)
{
	char *expanded;
	
	expanded = ft_getenv(exp_var, env_cpy);
	free(exp_var);
	return (expanded);
}

char	*replace_expanded_variable(char *word_var, char *exp_var, int start)
{
	char	*new_line;
	int		index;
	int		index_word;
	int		index_exp;
	
	new_line = ft_calloc(ft_strlen(word_var) + ft_strlen(exp_var) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	index = 0;
	index_word = 0;
	index_exp = 0;
	while (index_word < start)
	{
		new_line[index] = word_var[index_word];
		index++;
		index_word++;
	}
	while (exp_var[index_exp])
	{
		new_line[index] = exp_var[index_exp];
		index++;
		index_exp++;
	}
	if (word_var[index_word] == '$')
		index_word++;
	while (word_var[index_word] && (ft_isalpha(word_var[index_word]) || word_var[index_word] == '_'))
		index_word++;
	while (word_var[index_word])
	{
		new_line[index] = word_var[index_word];
		index++;
		index_word++;
	}
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

char	*env_expander_loop(char *word_var, char **env_cpy)
{
	int	index;

	index = 0;
	while (word_var[index])
	{
		if (word_var[index] == '\'')
		{
			index++;
			while (word_var[index] != '\'')
				index++;
			if (word_var[index] == '\0')
				return (word_var);
		}
		if (word_var[index] == '$' && word_var[index + 1] && ft_isalpha(word_var[index + 1]))
		{
			word_var = expand_variable(word_var, &index, env_cpy);
			if (!word_var)
				return (NULL);
		}
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
			splitted_line[index] = env_expander_loop(splitted_line[index], env_cpy);
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
