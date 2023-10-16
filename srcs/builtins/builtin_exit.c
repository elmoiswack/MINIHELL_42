#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	ft_strisdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	convert_exit_code(int exit_code)
{
	while (exit_code > 255)
		exit_code -= 256;
	return (exit_code);
}

int execute_exit(t_lexer *node)
{
	int exit_code;
	if (!node->content[1])
	{
		if (!node->next)
		{
			ft_putstr_fd("exit\n", STDIN_FILENO);
			exit(0);
		}
		else 
			exit(1);
	}
	else if (node->content[2])
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	}
	else if (node->content[1][0] == '-' && ft_isdigit(node->content[1][1]) == 0)
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
	else if (ft_strisdigit(node->content[1]) || (node->content[1][0] == '-' && ft_strisdigit(&node->content[1][1])))
	{
		if (node->content[1][0] == '-')
			exit_code = ft_atoi(&node->content[1][1]);
		else
			exit_code = ft_atoi(node->content[1]);
		if (exit_code > 255 || exit_code < 0)
			exit_code = convert_exit_code(exit_code);
		ft_putstr_fd("exit\n", STDIN_FILENO);
		exit(exit_code);
	}
	ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
	return (1);
}
