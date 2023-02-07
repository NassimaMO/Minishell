/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/05 14:44:07 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(char **history)
{
	char	*str;
	char	buff[1];
	int		bytes;
	size_t	cursor;
	size_t	moves;

	set_terminal(SET);
	bytes = read(0, ft_memset(buff, 0, 1), 1);
	history = add_split(history, ft_strdup(""));
	ft_bzero((ft_bzero(&cursor, sizeof(size_t)), &moves), sizeof(size_t));
	while (history[split_len(history) - (moves + 1)] && bytes >= 0 && \
			*buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 4) && \
				!*history[split_len(history) - (moves + 1)])
			return (free_split(history), set_terminal(RESET), NULL);
		process_input(history, buff, &moves, &cursor);
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	if (bytes < 0 && *buff == 0)
		return (ft_printf("\n"), free_split(history), set_terminal(RESET), \
		ft_strdup(""));
	str = ft_strdup(history[split_len(history) - (moves + 1)]);
	free_split(history);
	return (ft_printf("\n"), set_terminal(RESET), str);
}
