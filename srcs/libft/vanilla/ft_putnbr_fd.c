/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:24:04 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/12 10:24:06 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int	nb;
	char			c;

	if (fd == -1)
		return ;
	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 0 && nb <= 9)
	{
		c = nb + '0';
		write(fd, &c, 1);
		return ;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		c = (nb % 10) + '0';
		write(fd, &c, 1);
	}
}
