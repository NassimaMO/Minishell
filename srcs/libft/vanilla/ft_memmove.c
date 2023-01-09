/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:43:38 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 12:43:40 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

static long unsigned int	ft_abs(long int n)
{
	if (n < 0)
		return ((unsigned)(-1 * n));
	return (n);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest && src && (dest > src && ft_abs(dest - src) < n))
	{
		i = n - 1;
		while (i != 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
		((char *)dest)[0] = ((char *)src)[0];
	}
	else
	{
		i = 0;
		while (dest && src && i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}
