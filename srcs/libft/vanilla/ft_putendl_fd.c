/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:21:34 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/12 10:21:36 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

static int	ft_strlen_(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (fd == -1 || !s)
		return ;
	write(fd, s, ft_strlen_(s));
	write(fd, "\n", 1);
}
