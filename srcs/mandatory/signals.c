/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:15 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/09 15:22:16 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t g_pid;

void	ft_handler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGINT)
		ft_printf("\n");
	if (signum == SIGQUIT && info->si_pid == g_pid)
	{
	}
	(void)context;
}

void	signals(void)
{
	struct sigaction		sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = &ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
