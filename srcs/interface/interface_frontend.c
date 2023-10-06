#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

void	init_ascii_art(void)
{
	char	*sc_line;
	int		sc_fd;

	sc_fd = open("./data/interface_ascii_header", O_RDONLY);
	if (sc_fd < 0)
	{
		ft_printf("ERROR OPENING ASCII ART\n");
		return ;
	}
	sc_line = get_next_line(sc_fd);
	while (sc_line)
	{
		ft_printf("\033[0;31m \033[1m%s", sc_line);
		free(sc_line);
		sc_line = get_next_line(sc_fd);
	}
}

void	remove_ctl_echo(void)
{
	struct termios	term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
}
