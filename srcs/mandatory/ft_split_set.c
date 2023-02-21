/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:27:23 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/15 17:50:42 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_trim_but_no(char *str, char c)
{
	char	*to_return;
	int		i;
	int		j;

	i = 0;
	j = 0;
	to_return = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			if (!str[i])
				break ;
			if (j)
				to_return[j++] = c;
		}
		to_return[j++] = str[i];
		i++;
	}
	return (to_return);
}

static int	is_char_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	**alloc_split(char *str, char *charset)
{
	int		i;
	int		j;
	int		compteur;
	char	**split;

	i = -1;
	compteur = 0;
	while (str[++i])
	{
		j = i;
		while (str[j] && !is_char_in_str(str[j], charset))
			j++;
		if (j != i)
		{
			compteur ++;
			i = j;
			while (str[j] && is_char_in_str(str[j], charset))
				j++;
			i = j - 1;
		}
	}
	split = malloc(sizeof(char *) * (compteur + 1));
	if (split)
		split[compteur] = 0;
	return (split);
}

char	**ft_split_set(char *str, char *charset)
{
	char	**split;
	int		i;
	int		j;
	int		compteur;

	split = alloc_split(str, charset);
	i = 0;
	compteur = 0;
	while (split && str[i])
	{
		j = i;
		while (str[j] && !is_char_in_str(str[j], charset))
			j++;
		if (j != i)
		{
			split[compteur++] = malloc(j - i + 1);
			ft_strlcpy(split[compteur - 1], str + i, j - i + 1);
			while (str[j] && is_char_in_str(str[j], charset))
				j++;
			i = j;
		}
		else
			i ++;
	}
	return (split);
}
