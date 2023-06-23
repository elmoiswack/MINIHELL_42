/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_word_counter_quotations.c                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/30 15:51:58 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/30 15:59:24 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_delimiter(char const *s, char c, int *i)
{
	while (s[*i] == c && s[*i])
		(*i)++;
}

static void	ft_skip_text(char const *s, char c, int *i)
{
	while (s[*i] != c && s[*i])
		(*i)++;
}

static int	ft_skip_till_quotations(char const *s, int *i)
{
	while (s[*i])
	{
		(*i)++;
		if (s[*i] == 39 || s[*i] == 34)
			return ((*i)++);
	}
	return (*i);
}

int	ft_word_counter_quotations(char const *s, char c)
{
	int		i;
	int		w_count;

	i = 0;
	w_count = 0;
	ft_skip_delimiter(s, c, &i);
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
			ft_skip_till_quotations(s, &i);
		else
			ft_skip_text(s, c, &i);
		w_count++;
		ft_skip_delimiter(s, c, &i);
	}
	return (w_count);
}
