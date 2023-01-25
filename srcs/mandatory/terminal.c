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

/* 
tty.c_lflag &= ~ECHO;
tty.c_lflag &= ~ICANON;
tty.c_lflag &= ~ECHOCTL;
*/

void	set_terminal(int option)
{
	struct termios			tty;
	static struct termios	tmp;

	if (option == SET)
	{
		tcgetattr(STDIN_FILENO, &tty);
		tmp = tty;
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	}
	else if (option == RESET)
		return ((void)tcsetattr(STDIN_FILENO, TCSANOW, &tmp));
}
