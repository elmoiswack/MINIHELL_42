#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void	init_ascii_art(void)
{
	char	*header_line;
	int		sc_fd;

	sc_fd = open("./data/interface_ascii_header", O_RDONLY);
	if (sc_fd < 0)
	{
		ft_printf("ERROR OPENING ASCII ART\n");
		return ;
	}
	header_line = get_next_line(sc_fd);
	while (header_line)
	{
		ft_printf("\033[0;31m \033[1m%s", header_line);
		free(header_line);
		header_line = get_next_line(sc_fd);
	}
	ft_printf("\033[0m");
}

void	init_history(void)
{
	char	*history_line;
	int		history_fd;

	history_fd = open("./data/minishell_history", O_RDWR | O_CREAT, 0644);
	if (history_fd < 0)
		return (perror("init_history()"));
	history_line = get_next_line(history_fd);
	while (history_line)
	{
		add_history(history_line);
		free(history_line);
		history_line = get_next_line(history_fd);
	}
}

void	add_to_history_file(char *line)
{
	int	history_fd;

	history_fd = open("./data/minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (history_fd < 0)
		return (perror("add_history_to_file()"));
	ft_putstr_fd(line, history_fd);
	ft_putstr_fd("\n", history_fd);
}

void	remove_ctl_echo(void)
{
	struct termios	term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
}
