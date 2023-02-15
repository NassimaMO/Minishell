/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:42:07 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/15 09:42:11 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt_hist(size_t *cursor, size_t *moves, char **history)
{
	ft_printf("\033[J\r");
	print_shell(0);
	ft_printf("%s", history[split_len(history) - (*moves + 1)]);
	*cursor = ft_strlen(history[split_len(history) - (*moves + 1)]);
}

void	go_through_hist(size_t *cursor, size_t *moves, char **history, int len)
{
	struct winsize	w;
	int				x;
	int				y;

	get_cursor_pos((ioctl(0, TIOCGWINSZ, &w), &x), &y);
	if (split_len(history) >= (*moves + 1) && y == w.ws_row && \
		len + print_shell(LEN) > w.ws_col)
	{
		while (len + print_shell(LEN) / w.ws_col > 0 && len > 0)
		{
			ft_printf("\033[1K\033[A");
			len -= w.ws_col;
		}
		print_prompt_hist(cursor, moves, history);
	}
	else if (split_len(history) >= (*moves + 1))
		print_prompt_hist((ft_printf("\033[u"), cursor), moves, history);
	else
		(*moves)--;
}
