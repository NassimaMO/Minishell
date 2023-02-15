/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:03:19 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/15 17:03:21 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_curs(t_cursor *curs, char direction, int n)
{
	struct winsize	w;
	int				i;

	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	while (i < n)
	{
		if (direction == LEFT && curs->x % w.ws_col == 1)
		{
			curs->x = w.ws_col;
			curs->y--;
		}
		else if (direction == RIGHT && curs->x % w.ws_col == 0)
		{
			curs->x = 1;
			curs->y++;
		}
		else if (direction == LEFT)
			curs->x--;
		else if (direction == RIGHT)
			curs->x++;
		i++;
	}
}

static void	print_prompt_hist(t_cursor *curs, size_t *moves, char **history, \
size_t s_len)
{
	ft_printf("\r\033[J\r");
	print_shell(0);
	curs->x = print_shell(LEN) + 1;
	ft_printf("%s", history[s_len - (*moves + 1)]);
	curs->cursor = ft_strlen(history[s_len - (*moves + 1)]);
	change_curs(curs, RIGHT, curs->cursor);
}

static void	go_through_hist(t_cursor *curs, size_t *moves, char **history, \
int len)
{
	struct winsize	w;
	int				sh_len;
	size_t			s_len;

	sh_len = print_shell(LEN);
	s_len = split_len(history);
	ioctl(0, TIOCGWINSZ, &w);
	if (s_len >= (*moves + 1))
	{
		while (len + sh_len / w.ws_col > 0 && len > 0 && len + sh_len > \
		w.ws_col)
		{
			ft_printf("\033[1K\033[A");
			curs->y--;
			len -= w.ws_col;
		}
		print_prompt_hist(curs, moves, history, s_len);
	}
	else
		(*moves)--;
}

void	ft_escape(t_cursor *curs, size_t *moves, char **history)
{
	char	buff[1];
	size_t	prec_move;

	prec_move = *moves;
	if (read(0, ft_memset(buff, 0, 1), 1) == 1 && *buff == '[')
	{
		read(0, ft_memset(buff, 0, 1), 1);
		if ((*buff == 'C' && curs->cursor < \
		ft_strlen(history[split_len(history) - (*moves + 1)]) && \
		++(curs->cursor)) || (*buff == 'D' && curs->cursor > 0 && \
		(--(curs->cursor), 1)))
			ft_move(curs, *buff, 1);
		if (history && ((*buff == 'A' && *moves < split_len(history) && \
		++(*moves)) || (*buff == 'B' && *moves > 0 && (--(*moves), 1))))
			go_through_hist(curs, moves, history, \
			ft_strlen(history[split_len(history) - (prec_move + 1)]));
	}
}
