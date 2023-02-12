/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:14 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/25 09:36:15 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(int *fd, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		fd[i] = i;
		i++;
	}
}

void	set_std(int std[2], int opt)
{
	if (!std)
		return ;
	if (opt == SET)
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		return ;
	}
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	ft_close(2, std[0], std[1]);
}

void	set_terminal(int option)
{
	struct termios			tty;
	static struct termios	tmp;

	if (option == SET)
	{
		tcgetattr(STDIN_FILENO, &tty);
		tmp = tty;
		tty.c_lflag &= ~ECHO;
		tty.c_lflag &= ~ICANON;
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	}
	else if (option == RESET)
		return ((void)tcsetattr(STDIN_FILENO, TCSANOW, &tmp));
}
