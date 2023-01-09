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
	{
		printf("\n");
		print_shell();
	}
}

void	control_c(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handler;
	sigaction(SIGINT, &sa, NULL);
}
