/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:33:17 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 12:33:20 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	long unsigned int	i;

	i = 0;
	while (s1 && s2 && i < n)
	{
		if (((char *)s1)[i] != ((char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
