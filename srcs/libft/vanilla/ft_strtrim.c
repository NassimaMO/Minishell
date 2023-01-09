/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:27:14 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/11 12:27:17 by nghulam-         ###   ########.fr       */
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

static int	char_in_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if ((unsigned char)c == (unsigned char)set[i])
			return (1);
		if (ft_isspace((unsigned char)c))
			return (1);
		i++;
	}
	return (0);
}

static char	*void_chain(void)
{
	char	*new_s;

	new_s = malloc(1);
	if (!new_s)
		return ((char *)0);
	new_s[0] = 0;
	return (new_s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new_s;
	int		i;

	start = 0;
	while (s1 && set && s1[start] && char_in_set(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > 0 && char_in_set(set, s1[end - 1]))
		end --;
	if (end <= start)
		return (void_chain());
	new_s = malloc((end - start) + 1);
	if (!new_s)
		return ((char *)0);
	new_s[end - start] = 0;
	i = 0;
	while (i < end - start)
	{
		new_s[i] = s1[start + i];
		i++;
	}
	return (new_s);
}
