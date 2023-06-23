/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:43:21 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:35:07 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != (char)c)
		i++;
	return (i);
}

char	*read_buffer(int fd, char *btnl)
{
	char		*temp;
	int			bytes;

	temp = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!temp)
		return (NULL);
	bytes = 1;
	while ((!ft_strchr(btnl, '\n') && bytes > 0))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(temp), free(btnl), NULL);
		temp[bytes] = '\0';
		btnl = ft_strjoin_and_free(btnl, temp);
	}
	free(temp);
	return (btnl);
}

char	*filter_tnl(char *btnl)
{
	int		nl_index;
	char	*current_line;

	if (btnl[0] == '\0')
		return (NULL);
	nl_index = ft_strchr_index(btnl, '\n');
	current_line = ft_substr(btnl, 0, nl_index + 1);
	if (!current_line)
		return (free(btnl), NULL);
	return (current_line);
}

char	*trim_tnl(char *btnl)
{
	int		nl_index;
	char	*new_btnl;

	if (!(ft_strchr(btnl, '\n')))
		return (free(btnl), NULL);
	nl_index = ft_strchr_index(btnl, '\n');
	new_btnl = ft_substr(btnl, nl_index + 1, ft_strlen(btnl) + nl_index + 1);
	free(btnl);
	return (new_btnl);
}

char	*get_next_line(int fd)
{
	static char	*btnl;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	btnl = read_buffer(fd, btnl);
	if (btnl == NULL)
		return (NULL);
	current_line = filter_tnl(btnl);
	btnl = trim_tnl(btnl);
	return (current_line);
}

// int	main()
// {
// 	int 	fd_a;
// 	int		fd_b;
// 	int		i;
// 	char	*line_a;

// 	i = 0;
// 	fd_a = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line_a = get_next_line(fd_a);
// 		printf("Line[%d]: %s\n", i, line_a);
// 		if (line_a == NULL)
// 			break ;
// 		i++;
// 	}
// 	close(fd_a);
// }
