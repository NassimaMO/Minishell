/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:33:34 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/11 14:33:36 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

static long unsigned int	ft_abs(int n)
{
	if (n < 0)
		return ((unsigned)(-1 * n));
	return (n);
}

static int	count_num(long unsigned int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		n /= 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int					count;
	int					i;
	long unsigned int	n2;
	char				*s;

	n2 = ft_abs(n);
	count = count_num(n2);
	s = malloc(count + 1 + (n < 0));
	if (!s)
		return ((char *)0);
	i = 0;
	n2 = ft_abs(n);
	while (i < count + (n < 0))
	{
		s[count - i - 1 + (n < 0)] = (n2 % 10) + '0';
		n2 /= 10;
		i++;
	}
	s[i] = 0;
	if (n < 0)
		s[0] = '-';
	return (s);
}
