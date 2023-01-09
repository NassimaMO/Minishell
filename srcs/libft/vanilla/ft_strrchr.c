/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:47:13 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 14:47:15 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s && s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if (j == -1)
	{
		if (s && s[i] == c)
			return ((char *)s + i);
		return ((char *)0);
	}
	return ((char *)s + j);
}
