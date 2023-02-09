/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:27 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/05 15:20:50 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_dup(char **split)
{
	char	**to_return;
	int		i;

	if (!split)
		return (NULL);
	to_return = malloc(sizeof(char *) * (split_len(split) + 1));
	i = 0;
	while (split && split[i])
	{
		to_return[i] = ft_strdup(split[i]);
		i++;
	}
	to_return[i] = NULL;
	return (to_return);
}

char	**add_split(char **split, char *str)
{
	int		i;
	char	**new_split;

	i = 0;
	while (split && split[i])
		i++;
	new_split = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (split && split[i])
	{
		new_split[i] = split[i];
		i++;
	}
	new_split[i] = str;
	new_split[i + 1] = NULL;
	free(split);
	return (new_split);
}

char	*ft_dupfree(char **split, int i)
{
	char	*tmp;

	tmp = ft_strdup(split[i]);
	free_split(split);
	return (tmp);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

size_t	split_len(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
