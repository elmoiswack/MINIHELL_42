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

t_lexer	*parsing_line(t_lexer *info_list, char *line)
{
	char	**splitted_line;
	int		*enum_array;
	int		index;

	index = 0;
	splitted_line = super_split(line);
	while (splitted_line[index])
		index++;
	enum_array = ft_calloc(index + 1, sizeof(int));
	if (!enum_array)
		return (NULL);
	enum_array = into_enum_array(splitted_line, enum_array);
	index = 0;
	while (splitted_line[index])
	{
		printf("line = %s\n", splitted_line[index]);
		printf("enum_awa = %i\n", enum_array[index]);
		index++;
	}
	info_list = organizing_data(info_list, splitted_line, enum_array);
	return (info_list);
}

t_lexer	*lexing(char *line)
{
	int		ammount_words;
	t_lexer	*info_list;

	info_list = ft_calloc(1, sizeof(t_lexer));
	if (!info_list)
		return (NULL);
	line = put_spaces_in_line(line);
	ammount_words = ammount_of_words(line);
	if (ammount_words == 1)
		return (one_word_lexer(info_list, line));
	if (ammount_words == 2)
		return (two_word_lexer(info_list, line));
	if (ammount_words > 2)
		info_list = parsing_line(info_list, line);
	free(line);
	return (info_list);
}
