#include "../../libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool	is_directory(char *content)
{
	struct stat	path_stat;

	if (stat(content, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}
