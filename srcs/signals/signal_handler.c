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

static void	handle_hd_signals(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 131;
		kill(getpid(), SIGINT);
		exit(130);
	}
}

static void	handle_child_int(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		kill(getpid(), SIGINT);
		exit(130);
	}
}

static void	handle_child_quit(int signum)
{
	if (signum == SIGQUIT)
	{
		g_exit_status = 0;
		kill(getpid(), SIGQUIT);
		exit(0);
	}
}

void	change_signal_profile(t_sig_profile profile)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;

	ft_memset(&s_int, 0, sizeof(s_int));
	ft_memset(&s_quit, 0, sizeof(s_quit));
	if (profile == CHILD)
	{
		s_int.sa_handler = &handle_child_int;
		s_quit.sa_handler = &handle_child_quit;
	}
	else if (profile == PARENT)
	{
		s_int.sa_handler = &handle_parent_signals;
		s_quit.sa_handler = SIG_IGN;
	}
	else if (profile == HD)
	{
		s_int.sa_handler = &handle_hd_signals;
		s_quit.sa_handler = SIG_IGN;
	}
	if (sigaction(SIGINT, &s_int, NULL) == -1)
		perror("SIGINT: ");
	if (sigaction(SIGQUIT, &s_quit, NULL) == -1)
		perror("SIGINT: ");
}
