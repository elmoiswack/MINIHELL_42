#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// static bool	print_env(char *input, char *envp[], int *i)
// {
// 	char	*value;
//
// 	value = NULL;
// 	if (arg_is_env(&input[*i], &value, envp) == 1)
// 	{
// 		*i += ft_printf("%s", value) + 1;
// 		return (free(value), true);
// 	}
// 	return (free(value), false);
// }
//

static int	output_trailing_newline(char *raw_input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (raw_input[i])
	{
		if (raw_input[i] == '-' && raw_input[i + 1] != '\0'
			&& raw_input[i + 1] == 'n' && ft_iswhitespace(raw_input[i + 2]))
		{
			j = i + 2;
			while (raw_input[j])
			{
				if (ft_iswhitespace(raw_input[j]))
					j++;
				if (!ft_iswhitespace(raw_input[j]) && ft_isprint(raw_input[j]))
					return (j);
				j++;
			}
		}
		i++;
	}
	return (0);
}

static bool	print_pid(char *input, int *i)
{
	if (input[*i] == '$' && input[*i + 1] != '\0' && input[*i + 1] == '$')
	{
		ft_printf("%d", (int)getpid());
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
			ft_putstr_fd(value, STDIN_FILENO);
			(*i)++;
			return (free(value), true);
		}
		else if (value && !ft_isalnum(input[(*i) - 1]) && input[(*i)] == '~'
			&& input[(*i) - 1] != '~')
		{
			ft_putstr_fd(value, STDIN_FILENO);
			(*i)++;
			return (free(value), true);
		}
		free(value);
	}
	return (false);
}

static void	expand_and_print_input(char *input, char *envp[])
{
	int		i;

	i = 0;
	while (input[i])
	{
		// if (print_env(input, envp, &i))
		// 	continue ;
		if (print_pid(input, &i))
			continue ;
		else if (print_home(input, envp, &i))
			continue ;
		else if (input[i] != '\0')
			write(STDIN_FILENO, &input[i], 1);
		i++;
	}
}

void	execute_echo(char **raw_input, char *envp[])
{
	char	*line;
	int		line_start;

	if (!raw_input[1] || raw_input[1][0] == '\0')
		return (ft_putstr_fd("\n", STDOUT_FILENO));
	else if (raw_input[1][0] == '-' && raw_input[1][1] == 'n'
		&& raw_input[1][2] == '\0')
		return ;
	else if (raw_input[1][0] == '-' && raw_input[1][1] == 'n'
		&& raw_input[1][2] == ' ' && raw_input[1][3] == '\0')
		return ;
	line_start = output_trailing_newline(raw_input[1]);
	line = &raw_input[1][line_start];
	if (ft_strncmp(line, "$?", ft_strlen(line)) == 0)
		ft_printf("%d", g_exit_status);
	else
		expand_and_print_input(line, envp);
	if (line_start == 0)
		ft_printf("\n");
	g_exit_status = 0;
}
