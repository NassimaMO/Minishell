/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:15 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 16:30:44 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handler(int signum)
{
	struct termios	tty;

	if (signum == SIGINT)
	{
		g_exit_code = 130;
		tcgetattr(STDIN_FILENO, &tty);
		if (!(tty.c_lflag & ECHO) || !(tty.c_lflag & ECHOCTL))
			ft_printf("^C");
	}
}

static void	handler_heredoc(int signum, siginfo_t *info, void *context)
{
	struct termios	tty;

	if (signum == SIGINT)
	{
		g_exit_code = 130;
		tcgetattr(STDIN_FILENO, &tty);
		if (!(tty.c_lflag & ECHO) || !(tty.c_lflag & ECHOCTL))
			ft_printf("^C\n");
		signals(RESET);
		kill(SIGINT, info->si_pid);
	}
	(void)context;
}

void	signals(int option)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	if (option == SET)
		sa.sa_handler = &ft_handler;
	else if (option == HEREDOC)
	{
		sa.sa_flags |= SA_SIGINFO;
		sa.sa_sigaction = &handler_heredoc;
	}
	else if (option == RESET)
		sa.sa_handler = SIG_DFL;
	else if (option == IGNORE)
		sa.sa_handler = SIG_IGN;
	else
		return ;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}
