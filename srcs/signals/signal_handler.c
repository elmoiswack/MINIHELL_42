/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:21:41 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/11/01 12:39:04 by dantehussai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	}
}

static void	handle_waiting_signals(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
}

static void	handle_hd_signals(int signum)
{
	if (signum == SIGINT)
		exit(130);
}

void	change_signal_profile(t_sig_profile profile)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;

	sigemptyset(&s_int.sa_mask);
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_handler = SIG_IGN;
	s_int.sa_flags = SA_RESTART;
	s_quit.sa_flags = SA_RESTART;
	if (profile == CHILD)
	{
		s_int.sa_handler = SIG_DFL;
		s_quit.sa_handler = SIG_DFL;
	}
	else if (profile == PARENT)
		s_int.sa_handler = &handle_parent_signals;
	else if (profile == HD)
		s_int.sa_handler = &handle_hd_signals;
	else if (profile == WAITING)
		s_int.sa_handler = &handle_waiting_signals;
	if (sigaction(SIGINT, &s_int, NULL) == -1
		|| sigaction(SIGQUIT, &s_quit, NULL) == -1)
		perror("SIGACTION: ");
}
