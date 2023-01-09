/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:14:54 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 14:14:56 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	if (!s)
		return (malloc(0));
	while (s[i])
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (dup);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = (char)0;
	return (dup);
}
