#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

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
	return (COMMAND);
}

int	*into_enum_array(char **splitted_line, int *enum_array)
{
	int	index_array;
	int	index_line;

	index_array = 0;
	index_line = 0;
	while (splitted_line[index_line])
	{
		enum_array[index_array] = which_enum(splitted_line, index_line);
		if (enum_array[index_array] == REDIRECT_IN)
		{
			index_array++;
			index_line++;
			if (splitted_line[index_line][0] == '$')
				enum_array[index_array] = ENV_VAR;
			else
				enum_array[index_array] = INFILE;
		}
		else if(enum_array[index_array] == REDIRECT_OUT)
		{
			index_array++;
			index_line++;
			if (splitted_line[index_line][0] == '$')
				enum_array[index_array] = ENV_VAR;
			else
				enum_array[index_array] = OUTFILE;
		}
		index_line++;
		index_array++;
	}
	enum_array[index_array] = 0;
	return (enum_array);
}

t_lexer	*parsing_array(t_lexer *info_list, char **splitted_line, int *enum_array)
{
	int		index;
	int		ammount_words;

	ammount_words = 0;
	index = 0;
	if (check_for_envvar(splitted_line, enum_array) == 1)
	{
		splitted_line = edit_arr_env(splitted_line, enum_array);
		free(enum_array);
		while (splitted_line[index])
			index++;
		enum_array = ft_calloc(index, sizeof(int));
		if (!enum_array)
			return (NULL);
		enum_array = into_enum_array(splitted_line, enum_array);
	}
	while (splitted_line[ammount_words])
		ammount_words++;
	if (ammount_words == 1)
		return (one_word_lexer(info_list, splitted_line));
	if (ammount_words == 2)
		return (two_word_lexer(info_list, splitted_line));
	if (ammount_words > 2)
		info_list = organizing_data(info_list, splitted_line, enum_array);
	return (info_list);
}

t_lexer	*lexing(char *line)
{
	char	**splitted_line;
	int		*enum_array;
	t_lexer	*info_list;
	int		index;

	index = 0;
	info_list = ft_calloc(1, sizeof(t_lexer));
	if (!info_list)
		return (NULL);
	line = put_spaces_in_line(line);
	if (check_for_quotes(line) == 1)
		splitted_line = split_with_quotes(line);
	else
		splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		return (NULL);
	while (splitted_line[index])
		index++;
	enum_array = ft_calloc(index + 1, sizeof(int));
	if (!enum_array)
		return (NULL);
	enum_array = into_enum_array(splitted_line, enum_array);
	info_list = parsing_array(info_list, splitted_line, enum_array);
	free(line);
	free(enum_array);
	return (info_list);
}
