/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   error.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 15:28:07 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/26 12:39:28 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	error_lexing_message(t_lexer *list)
{
	if (list->error_code == 1)
		printf("%s\n", list->error_str);
	if (list->error_code == 2)
		printf("Syntax error, %s\n", list->error_str);
	if (list->error_code == 3)
		printf("Allocation error at %s\n", list->error_str);
}
