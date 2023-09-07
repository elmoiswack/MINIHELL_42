#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_parent_signals(int signum)
{	
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

static void	handle_child_signals(int signum)
{	
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "YEET\n", 4);
		g_exit_status = 130;
		kill(getpid(), SIGINT);
	}
	else if (signum == SIGQUIT)
	{
		write(STDERR_FILENO, "YEET\n", 4);
		g_exit_status = 131;
		kill(getpid(), SIGQUIT);
	}
}

void	catch_signals_parent(void)
{
	struct sigaction sigparent_int;
	struct sigaction sigparent_quit;

	sigparent_int.sa_handler = &handle_parent_signals;
	sigparent_quit.sa_handler = SIG_IGN;

	if (sigaction(SIGINT, &sigparent_int, NULL) == -1)
		perror("SIGINT: ");
	if (sigaction(SIGQUIT, &sigparent_quit, NULL) == -1)
		perror("SIGQUIT: ");
}

void	catch_signals_child(void)
{
	struct sigaction sigchild;

	sigchild.sa_handler = &handle_child_signals;
	if (sigaction(SIGINT, &sigchild, NULL) == -1)
		perror("SIGINT: ");
	if (sigaction(SIGQUIT, &sigchild, NULL) == -1)
		perror("SIGINT: ");
}
