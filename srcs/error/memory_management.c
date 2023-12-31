/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   memory_management.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:28:16 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/16 12:57:40 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	free_ll(t_lexer **lst)
{
	t_lexer	*current;

	current = *lst;
	while (current != NULL)
	{
		current = *lst;
		if (current->path)
			free(current->path);
		if (current->infile)
			free_double_array(current->infile);
		if (current->outfile)
			free_double_array(current->outfile);
		if (current->delim)
			free_double_array(current->delim);
		if (current->content)
			free_double_array(current->content);
		current = current->next;
		free(*lst);
		*lst = current;
	}
	free(*lst);
}

void	clean_up(t_minishell *shell)
{
	free_ll(&shell->cmd_lst);
}

char	**rev_free_arr(char **strings_array, int i)
{
	while (i >= 0)
	{
		free(strings_array[i]);
		i--;
	}
	free(strings_array);
	return (0);
}
