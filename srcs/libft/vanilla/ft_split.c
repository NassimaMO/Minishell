/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:05:30 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/11 13:05:32 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

static char	*ft_strncopy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static char	**alloc_split(const char *str, char c)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	i = -1;
	count = 0;
	while (str && str[++i])
	{
		j = i;
		while (str[j] && (unsigned char)c != (unsigned char)(str[j]))
			j++;
		if (j != i)
		{
			count ++;
			i = j;
			while (str[j] && (unsigned char)(str[j]) == (unsigned char)c)
				j++;
			i = j - 1;
		}
	}
	split = malloc(sizeof(char *) * (str != NULL) * (count + 1));
	if (str && split)
		split[count] = 0;
	return (split);
}

char	**ft_split(char const *str, char c)
{
	char	**split;
	int		i;
	int		j;
	int		count;

	split = alloc_split(str, c);
	i = 0;
	count = 0;
	while (str && split && str[i])
	{
		j = i;
		while (str[j] && (unsigned char)(str[j]) != (unsigned char)c)
			j++;
		if (j != i)
		{
			split[count++] = malloc(j - i + 1);
			ft_strncopy(split[count - 1], (char *)str + i, j - i);
			while (str[j] && (unsigned char)c == (unsigned char)(str[j]))
				j++;
			i = j;
		}
		else
			i ++;
	}
	return (split);
}
