/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtin_echo.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:13:17 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/24 13:39:20 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static int	output_trailing_newline(char *raw_input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (raw_input[i])
	{
		if (raw_input[i] == '-')
		{
			j = i + 1;
			while (raw_input[j] && !ft_iswhitespace (raw_input[j])
				&& raw_input[j] == 'n' && raw_input[j] != '-')
				j++;
			if (ft_isalpha(raw_input[j]))
				return (i);
			i = j;
		}
		else if (ft_isascii(raw_input[i]))
			return (i);
		i++;
	}
	if (i > (int)ft_strlen(raw_input))
		return (-1);
	return (j + 1);
}

static bool	print_pid(char *input, int *i)
{
	if (input[*i] == '$' && input[*i + 1] != '\0' && input[*i + 1] == '$')
	{
		ft_putstr_fd(ft_itoa((int)getpid()), STDOUT_FILENO);
		*i += 2;
		return (true);
	}
	return (false);
}

static bool	print_home(char *input, char *envp[], int *i)
{
	char	*value;

	value = NULL;
	if ((input[*i] == '~' && input[(*i) + 1] == '\0')
		|| (input[(*i)] == '~' && input[(*i) + 1] != '\0'
			&& input[(*i) + 1] != '~'))
	{
		value = ft_getenv("HOME", envp);
		if (value && *i == 0)
		{
			ft_putstr_fd(value, STDOUT_FILENO);
			(*i)++;
			return (free(value), true);
		}
		else if (value && !ft_isalnum(input[(*i) - 1]) && input[(*i)] == '~'
			&& input[(*i) - 1] != '~')
		{
			ft_putstr_fd(value, STDOUT_FILENO);
			(*i)++;
			return (free(value), true);
		}
		free(value);
	}
	return (false);
}

static void	expand_and_print_input(char *input, char *envp[], int status)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (print_pid(input, &i))
			continue ;
		else if (print_home(input, envp, &i))
			continue ;
		else if (ft_strncmp(&input[i], "$?", 2) == 0)
		{
			ft_putstr_fd(ft_itoa(status), STDOUT_FILENO);
			i++;
		}
		else if (input[i] != '\0')
			write(STDOUT_FILENO, &input[i], 1);
		i++;
	}
}

int	execute_echo(char **raw_input, char *envp[], int status)
{
	char	*line;
	int		line_start;

	if (!raw_input[1] || raw_input[1][0] == '\0')
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	else if (raw_input[1][0] == '-' && raw_input[1][1] == 'n'
		&& raw_input[1][2] == '\0')
		return (0);
	else if (raw_input[1][0] == '-' && raw_input[1][1] == 'n'
		&& raw_input[1][2] == ' ' && raw_input[1][3] == '\0')
		return (0);
	line_start = output_trailing_newline(raw_input[1]);
	if (line_start == -1)
		return (0);
	line = &raw_input[1][line_start];
	expand_and_print_input(line, envp, status);
	if (line_start == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
