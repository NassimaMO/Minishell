/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:27 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/31 16:00:17 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	free_env(int len)
{
	int	i;

	i = len;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
}
