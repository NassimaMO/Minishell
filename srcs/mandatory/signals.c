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
	if (signum == SIGINT)
		ft_printf("\n");
	if (signum == SIGQUIT)
	{
	}
}

void	signals(void)
{
	struct sigaction		sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &ft_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
