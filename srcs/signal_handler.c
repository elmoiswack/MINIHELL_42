#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void	handle_sigint(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n\033[0;37m \033[1m MINIHELL_\033[0m> ", 30);
}

void	catch_signals(void)
{
	struct sigaction interrupt;
	struct sigaction quit;

	interrupt.sa_handler = &handle_sigint;
	quit.sa_handler = SIG_IGN;

	sigaction(SIGINT, &interrupt, NULL);
	sigaction(SIGQUIT, &quit, NULL);
}

