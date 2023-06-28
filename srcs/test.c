#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	test_unset(char *argv[], char *envp[])
{
	int	var_index;
	char	**new_envp;

	var_index = 0;
	if (argv[1] == NULL)
		printf("argv[1] is null!\n");
	var_index = var_exists(envp, argv[1], strlen(argv[1]));
	printf("var_index: %d\n", var_index);
	if (var_index >= 0)
		new_envp = remove_str_from_array(envp, var_index);
	// print_double_array(new_envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	print_double_array(envp);
	printf("\n");
	test_unset(argv, envp);
}
