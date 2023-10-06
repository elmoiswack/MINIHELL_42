#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static bool	print_env(char *input, char *envp[], int *i)
{
	char	*value;

	value = NULL;
	if (arg_is_env(&input[*i], &value, envp) == 1)
	{
		*i += ft_printf("%s", value) + 1;
		return (free(value), true);
	}
	return (free(value), false);
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

static void	expand_and_print_input(char **input, char *envp[])
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[j])
	{
		while (input[j][i])
		{
			if (print_env(input[j], envp, &i))
				continue ;
			else if (print_pid(input[j], &i))
				continue ;
			else if (print_home(input[j], envp, &i))
				continue ;
			else if (input[j][i] != '\0')
				write(STDIN_FILENO, &input[j][i], 1);
			i++;
		}
		i = 0;
		j++;
	}
	write(STDIN_FILENO, "\n", 1);
}

void	execute_echo(char **raw_input, char *envp[])
{
	if (!raw_input[1])
		ft_printf("\n");
	else if (ft_strncmp(raw_input[1], "$?", ft_strlen(raw_input[1])) == 0)
		ft_printf("%d\n", g_exit_status);
	else
		expand_and_print_input(&raw_input[1], envp);
	g_exit_status = 0;
}
