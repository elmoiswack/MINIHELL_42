#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

//IN ASCII THE NUMBER 39 MEANS '

int	which_enum(char **splitted_line, int index)
{
	if (splitted_line[index][0] == '<' && splitted_line[index][1] != '<')
		return (REDIRECT_IN);
	if (splitted_line[index][0] == '<' && splitted_line[index][1] == '<')
		return (DELIMITER);
	if (splitted_line[index][0] == '>' && splitted_line[index][1] != '>')
		return (REDIRECT_OUT);
	if (splitted_line[index][0] == '>' && splitted_line[index][1] == '>')
		return (APPENDER);
	if (splitted_line[index][0] == '|')
		return (PIPE);
	if (splitted_line[index][0] == '$' && ft_isalpha(splitted_line[index][1]))
		return (ENV_VAR);
	if (splitted_line[index][0] == '-' && ft_isalpha(splitted_line[index][1]))
		return (FLAG);
	if (splitted_line[index][0] == 39 && ft_isalpha(splitted_line[index][1]))
		return (FLAG);
	return (COMMAND);
}

int	*into_enum_array(char **splitted_line, int *enum_array, int index)
{
	while (splitted_line[index])
	{
		enum_array[index] = which_enum(splitted_line, index);
		if (enum_array[index] == REDIRECT_IN)
		{
			index++;
			if (splitted_line[index][0] == '$')
				enum_array[index] = ENV_VAR;
			else
				enum_array[index] = INFILE;
		}
		else if (enum_array[index] == REDIRECT_OUT)
		{
			index++;
			if (splitted_line[index][0] == '$')
				enum_array[index] = ENV_VAR;
			else
				enum_array[index] = OUTFILE;
		}
		index++;
	}
	enum_array[index] = 0;
	return (enum_array);
}

t_lexer	*parsing_array(t_lexer *info_list, \
	char **splitted_line, int *enum_array)
{
	int		index;
	int		ammount_words;

	ammount_words = 0;
	index = 0;
	while (splitted_line[ammount_words])
		ammount_words++;
	if (ammount_words == 1)
	{
		info_list->check_free = 1;
		return (one_word_lexer(info_list, splitted_line));
	}
	if (ammount_words == 2)
	{
		info_list->check_free = 1;
		return (two_word_lexer(info_list, splitted_line));
	}
	if (ammount_words > 2)
		info_list = organizing_data(info_list, splitted_line, enum_array, 0);
	return (info_list);
}

t_lexer	*which_case(t_lexer	*info_list, char **splitted_line, int *enum_array)
{
	int	index;

	enum_array = into_enum_array(splitted_line, enum_array, 0);
	if (check_for_envvar(splitted_line, enum_array) == 1)
	{
		splitted_line = edit_arr_env(splitted_line, enum_array);
		free(enum_array);
		index = get_max_array(splitted_line);
		enum_array = ft_calloc(index + 1, sizeof(int));
		if (!enum_array)
			return (NULL);
		enum_array = into_enum_array(splitted_line, enum_array, 0);
	}
	if (check_special_cases(splitted_line) == 1)
		return (which_special_case(info_list, splitted_line, enum_array));
	info_list = parsing_array(info_list, splitted_line, enum_array);
	if (check_for_grep(info_list) == 1)
		info_list = grep_parser(info_list, splitted_line);
	if (check_for_cat(info_list) == 1)
		info_list = cat_parser(info_list, splitted_line);
	if (info_list->check_free != 1)
		free_2d_array(splitted_line);
	free(enum_array);
	return (info_list);
}

t_lexer	*lexing(char *line)
{
	char	**splitted_line;
	int		*enum_array;
	int		index;
	t_lexer	*info_list;

	info_list = ft_calloc(1, sizeof(t_lexer));
	if (!info_list)
		return (NULL);
	info_list->check_free = -1;
	line = put_spaces_in_line(line);
	if (check_for_quotes(line) == 1)
		splitted_line = split_with_quotes(line);
	else
		splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		return (NULL);
	index = get_max_array(splitted_line);
	enum_array = ft_calloc(index + 1, sizeof(int));
	if (!enum_array)
		return (NULL);
	info_list = which_case(info_list, splitted_line, enum_array);
	//free(line); buggie shit
	return (info_list);
}
