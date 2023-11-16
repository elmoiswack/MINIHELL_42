#include "../../libft/libft.h"
#include "../include/tester.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	run_tests()
{
	char *line;
	int fd;
	pid_t pid;
	char *test[4] = {"/home/fvan-wij/Documents/Github_Projects/Minishell/minishell", "-c", "echo jo", NULL};

	if ((fd = open("./testcases.txt", O_RDONLY)) < 0)
		perror("fd: ");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return ;
		test[2] = strdup(line);
		pid = fork();
		if (pid == 0)
		{
			if (execve(test[0], test, NULL) < 0)
				perror("execve: ");
			exit(1);
		}
		free(line);
		usleep(10000);
	}
}

int	main(void)
{
	run_tests();
	return (0);
}
