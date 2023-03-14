/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 16:57:53 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input_readline(char **history, t_cursor *curs)
{
	char	*str;
	char	buff[1];
	int		bytes;
	size_t	moves;

	set_terminal(SET);
	get_cursor_pos(&(curs->x), &(curs->y));
	bytes = read(0, ft_memset(buff, 0, 1), 1);
	history = add_split(history, ft_strdup(""));
	ft_bzero((ft_bzero(&(curs->cursor), 8UL), &moves), 8UL);
	while (history[split_len(history) - (moves + 1)] && bytes >= 0 && \
			*buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 4) && \
				!*history[split_len(history) - (moves + 1)])
			return (free_split(history), set_terminal(0), NULL);
		process_input(history, buff, &moves, curs);
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	if (bytes < 0 && *buff == 0)
		return (ft_printf("\n"), free_split(history), \
		set_terminal(RESET), ft_strdup(""));
	str = ft_strdup(history[split_len(history) - (moves + 1)]);
	free_split((ft_move(curs, RIGHT, ft_strlen(str) - curs->cursor), history));
	return (ft_printf("\n"), set_terminal(RESET), str);
}

char	*get_input(void)
{
	char	*str;
	char	buff;
	int		bytes;

	bytes = read(0, ft_memset(&buff, 0, 1), 1);
	str = gnl_join(ft_strdup(""), &buff, 1);
	while (bytes >= 0 && buff != '\n')
	{
		if (((bytes == 0 || buff == 0 || buff == 4) && !*str))
			return (free(str), NULL);
		bytes = read(0, ft_memset(&buff, 0, 1), 1);
		str = gnl_join(str, &buff, 1);
	}
	if (bytes < 0 && buff == 0)
		return (free(str), ft_strdup(""));
	return (str);
}
