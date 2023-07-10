#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_sigint(int signum)
{	
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	catch_signals(void)
{
	struct sigaction interrupt;
	struct sigaction quit;

	interrupt.sa_handler = &handle_sigint;
	interrupt.sa_flags = SA_RESTART;

	quit.sa_handler = SIG_IGN;
	quit.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &interrupt, NULL) == -1)
		perror("SIGINT: ");
	if (sigaction(SIGQUIT, &quit, NULL) == -1)
		perror("SIGQUIT: ");
}
