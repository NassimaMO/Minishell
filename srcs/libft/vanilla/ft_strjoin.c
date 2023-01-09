/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:14:47 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/11 12:14:49 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		i;

	if (!s1 || !s2)
		return (malloc(0));
	new_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_s)
		return (new_s);
	i = 0;
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		new_s[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	new_s[i] = 0;
	return (new_s);
}
