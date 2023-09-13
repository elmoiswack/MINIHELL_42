#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*parsing_array(t_lexer *info_list, \
	char **splitted_line, int *enum_array)
{
	int		ammount_words;

	ammount_words = get_max_array(splitted_line);
	if (ammount_words == 1 || ammount_words == 2)
		info_list->check_free = 1;
	if (ammount_words == 1)
		return (one_word_lexer(info_list, splitted_line));
	if (ammount_words == 2)
		return (two_word_lexer(info_list, splitted_line));
	if (ammount_words > 2)
		info_list = organizing_data(info_list, splitted_line, enum_array, 0);
	return (info_list);
}

int	info_list_checker(t_lexer *info_list, char **splitted_line, int *enum_array)
{
	if (!info_list)
	{
		free_double_array(splitted_line);
		free(enum_array);
		return (-1);
	}
	return (1);
}

t_lexer	*which_case(t_lexer	*info_list, char **splitted_line, int *enum_array)
{
	enum_array = into_enum_array(splitted_line, enum_array, 0);         
	if (check_var_expander(splitted_line) == 1)
		splitted_line = replace_var_expander(info_list, splitted_line, info_list->env_copy);
	if (!splitted_line)
		return (NULL);
	if (check_special_cases(splitted_line) == 1)
		return (which_special_case(info_list, splitted_line, enum_array));
	info_list = parsing_array(info_list, splitted_line, enum_array);
	if (info_list_checker(info_list, splitted_line, enum_array) == -1)
		return (NULL);
	if (check_for_grep(info_list) == 1)
		info_list = grep_parser(info_list, splitted_line);
	if (info_list_checker(info_list, splitted_line, enum_array) == -1)
		return (NULL);
	if (check_for_cat(info_list) == 1)
		info_list = cat_parser(info_list, splitted_line);
	if (info_list_checker(info_list, splitted_line, enum_array) == -1)
		return (NULL);
	if (info_list->check_free != 1)
		free_double_array(splitted_line);
	free(enum_array);
	return (info_list);
}

t_lexer *set_nonalloc_vars(t_lexer *info_list)
{
	info_list->check_free = -1;
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->error_code = -1;
	info_list->index_delim = 0;
	return (info_list);
}

t_lexer	*lexing(char *line, char **env_cpy)
{
	char	**splitted_line;
	int		*enum_array;
	int		index;
	t_lexer	*info_list;

	info_list = ft_calloc(1, sizeof(t_lexer));
	if (!info_list)
		return (NULL);
	info_list->env_copy = env_cpy;
	info_list = set_nonalloc_vars(info_list);
	line = put_spaces_in_line(line, info_list);
	if (!line)
		return (set_error_lex(info_list, 3, "lexer.c/L96"), NULL);
	if (check_for_quotes(line) == 1)
		splitted_line = split_with_quotes(line, info_list);
	else
		splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		return (NULL);
	index = get_max_array(splitted_line);
	enum_array = ft_calloc(index + 1, sizeof(int));
	if (!enum_array)
		return (set_error_lex(info_list, 3, "lexer.c/106"), NULL);
	info_list = which_case(info_list, splitted_line, enum_array);
	return (info_list);
}
