/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:42:15 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 14:42:17 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little && !(*little))
		return ((char *)big);
	while (little && big && big[i] && i < len)
	{
		j = 0;
		while ((unsigned char)little[j] == (unsigned char)big[i + j] && \
		little[j] && big[i + j] && (i + j) < len)
			j++;
		if (!big[i + j] && little[j])
			return ((char *)0);
		if (!little[j] || j == len)
			return ((char *)big + i);
		i++;
	}
	return ((char *)0);
}
