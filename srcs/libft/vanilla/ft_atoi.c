/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:57:33 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 14:57:35 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\f' || c == '\v' || c == '\r')
		return (1);
	else if (c == ' ')
		return (1);
	return (0);
}

static int	str_into_int(char *nptr)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		n *= 10;
		n += nptr[i] - '0';
		i++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	p;

	i = 0;
	p = 1;
	if (!nptr)
		return (0);
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		p = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (0);
	return (p * str_into_int((char *)nptr + i));
}
