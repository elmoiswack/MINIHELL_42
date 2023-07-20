#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_lexer	*echo_with_meta(t_lexer *info_list, char **splitted_line, \
	int *enum_array)
{
	int	index;

	index = 1;
	info_list->content = allocate_2d_arr(ft_strlen(splitted_line[0]) + 1);
	if (!info_list->content)
		return (NULL);
	ft_strcpy(info_list->content[0], splitted_line[0]);
	info_list->path = get_path_of_command(splitted_line[0]);
	while (splitted_line[index] && \
		is_metacharachter(splitted_line[index][0]) != 1)
	{
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
			splitted_line[index]);
		if (splitted_line[index + 1] != NULL)
			info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
				" ");
		index++;
	}
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list = organizing_data(info_list, splitted_line, enum_array, index);
	if (!info_list)
		return (NULL);
	return (info_list);
}

t_lexer	*special_case_echo(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	while (splitted_line[index])
	{
		if (is_metacharachter(splitted_line[index][0]) == 1)
			return (echo_with_meta(info_list, splitted_line, enum_array));
		index++;
	}
	index = 1;
	info_list->content = allocate_2d_arr(ft_strlen(splitted_line[0]) + 1);
	if (!info_list->content)
		return (NULL);
	ft_strcpy(info_list->content[0], splitted_line[0]);
	while (splitted_line[index])
	{
		info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
			splitted_line[index]);
		if (splitted_line[index + 1] != NULL)
			info_list->content[1] = ft_strjoin_and_free(info_list->content[1], \
				" ");
		index++;
	}
	info_list->input = STDIN_IN;
	info_list->output = STDOUT_OUT;
	info_list->path = get_path_of_command(splitted_line[0]);
	info_list->next = NULL;
	return (info_list);
}

t_lexer	*special_case_rm(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index)
{
	info_list->input = NONE;
	info_list->output = NONE;
	info_list->content = allocate_2d_arr(ft_strlen(splitted_line[0]) + 1);
	if (!info_list->content)
		return (NULL);
	ft_strcpy(info_list->content[0], splitted_line[0]);
	info_list->path = get_path_of_command(splitted_line[0]);
	index = 1;
	if (enum_array[index] && enum_array[index] == FLAG)
	{
		info_list->content[index] = \
			ft_calloc(ft_strlen(splitted_line[index]) + 1, sizeof(char));
		if (!info_list->content[index])
			return (NULL);
		ft_strcpy(info_list->content[index], splitted_line[index]);
		index++;
	}
	info_list->content[index] = ft_calloc(ft_strlen(splitted_line[index]) + 1, \
		sizeof(char));
	if (!info_list->content[index])
		return (NULL);
	ft_strcpy(info_list->content[index], splitted_line[index]);
	info_list->next = NULL;
	return (info_list);
}

t_lexer	*which_special_case(t_lexer *info_list, char **splitted_line, \
	int *enum_array)
{
	if (ft_strncmp(splitted_line[0], "echo", ft_strlen(splitted_line[0])) == 0)
	{
		info_list = special_case_echo(info_list, splitted_line, enum_array, 0);
		free_2d_array(splitted_line);
		free(enum_array);
		return (info_list);
	}
	if (ft_strncmp(splitted_line[0], "rm", ft_strlen(splitted_line[0])) == 0)
	{
		info_list = special_case_rm(info_list, splitted_line, enum_array, 0);
		free_2d_array(splitted_line);
		free(enum_array);
		return (info_list);
	}
	return (NULL);
}

int	check_special_cases(char **splitted_line)
{
	if (ft_strncmp(splitted_line[0], "echo", ft_strlen(splitted_line[0])) == 0)
		return (1);
	if (ft_strncmp(splitted_line[0], "rm", ft_strlen(splitted_line[0])) == 0)
		return (1);
	return (-1);
}
