/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:14 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 17:09:05 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(int nb, ...)
{
	int		i;
	va_list	args;
	int		*n;

	i = 0;
	va_start(args, nb);
	while (i < nb)
	{
		n = va_arg(args, int *);
		*n = 0;
		i++;
	}
}

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

void	set_std(int std[3], int opt)
{
	if (!std)
		return ;
	if (opt == SET)
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		std[2] = dup(STDERR_FILENO);
		return ;
	}
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	dup2(std[2], STDERR_FILENO);
	ft_close(3, std[0], std[1], std[2]);
}

void	set_terminal(int option)
{
	struct termios			tty;
	static struct termios	tmp;
	int						fd[2];
	static int				std[3];
	struct stat				buf;

	if (option == SET && (set_std(std, SET), 1))
	{
		fd[0] = open("/dev/tty", O_RDONLY);
		fd[1] = open("/dev/tty", O_WRONLY);
		fstat(STDIN_FILENO, &buf);
		if (!S_ISFIFO(buf.st_mode))
			ft_dup(fd[0], fd[1]);
		else
			ft_close(2, fd[0], (close(STDOUT_FILENO), fd[1]));
		if (!isatty(STDIN_FILENO))
			return ;
		tmp = (tcgetattr(STDIN_FILENO, &tty), tty);
		tty.c_lflag &= ~ECHO;
		tty.c_lflag &= ~ICANON;
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	}
	else if (option == RESET && (set_std(std, RESET), isatty(STDIN_FILENO)))
		tcsetattr(STDIN_FILENO, TCSANOW, &tmp);
}
