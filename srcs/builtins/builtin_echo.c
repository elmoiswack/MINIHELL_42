#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	expand_and_print_input(char **input, char *envp[])
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (input[j])
	{
		while (input[j][i])
		{
			if (arg_is_env(&input[j][i], &value, envp) == 1)
			{
				i += ft_printf("%s", value) + 1;
				free(value);
			}
			else if (input[j][i] == '$' && input[j][i + 1] != '\0' && input[j][i + 1] == '$')
			{
				ft_printf("%d", (int)getpid());
				i++;
			}
			else if (input[j][i] == '~')
			{
				value = ft_getenv("HOME", envp);
				if (value)
				{
					ft_putstr_fd(value, STDIN_FILENO);
					free(value);
				}
			}
			else if (input[j][i] != '\0')
		 		write(STDIN_FILENO, &input[j][i], 1);
			i++;
		}
		i = 0;
		j++;
	}
	ft_printf("\n");
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
