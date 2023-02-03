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

void	ft_handler(int signum)
{
	(void)signum;
}

void	signals(void)
{
	struct sigaction		sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &ft_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}
