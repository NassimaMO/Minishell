/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:55:43 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/11 11:55:46 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

static char	*void_chain(void)
{
	char	*new_s;

	new_s = malloc(1);
	if (!new_s)
		return ((char *)0);
	new_s[0] = 0;
	return (new_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	long unsigned int	i;
	long unsigned int	j;
	char				*new_s;

	i = 0;
	while (s && s[i] && i < start)
		i++;
	if (!s || (!s[i] && i < start))
		return (void_chain());
	while (s[i] && i - start < len)
		i++;
	new_s = malloc(i - start + 1);
	if (!new_s)
		return ((char *)0);
	new_s[i - start] = 0;
	j = 0;
	while (j < i - start)
	{
		new_s[j] = s[start + j];
		j++;
	}
	return (new_s);
}
