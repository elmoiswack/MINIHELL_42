#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd_2d(char *s[], int fd)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[j])
		{
			write(fd, &s[i][j], 1);
			j++;
		}
		write(fd, "\n", 1);
		j = 0;
		i++;
	}
}
