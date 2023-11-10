/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:40:16 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/10 13:14:21 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	get_end_quote(char *line, int end, int which)
{
	end++;
	if (which == 1)
	{
		while (line[end])
		{
			if (line[end] == '"')
				return (end);
			end++;
		}
	}
	else
	{
		while (line[end])
		{
			if (line[end] == '\'')
				return (end);
			end++;
		}
	}
	return (-1);
}
