#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	free_ll(t_lexer **lst)
{
	t_lexer	*current;

	current = *lst;
	while (current != NULL)
	{
		current = *lst;
		if (current->path)
			free(current->path);
		if (current->input == INFILE || current->output == OUTFILE)
			free(current->file);
		if (current->delim)
			free(current->delim);
		if (current->content)
			free_double_array(current->content);
		current = current->next;
		free(*lst);
		*lst = current;
	}
}

void clean_up(t_minishell *shell)
{
	// free env_cpy
	free_double_array(shell->env_cpy);	

	// free lexer
	free_ll(&shell->cmd_lst);
}

void	free_double_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

