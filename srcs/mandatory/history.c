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
	ft_move(curs, LEFT, curs->cursor);
	ft_printf("\033[J");
	ft_printf("%s", history[s_len - (*moves + 1)]);
	curs->cursor = ft_strlen(history[s_len - (*moves + 1)]);
	change_curs(curs, RIGHT, curs->cursor);
	if (curs->x == 1)
		ft_printf("\n");
}

static void	go_through_hist(t_cursor *curs, size_t *moves, char **history, \
int len)
{
	struct winsize	w;
	size_t			s_len;

	s_len = split_len(history);
	ioctl(0, TIOCGWINSZ, &w);
	if (s_len >= (*moves + 1))
	{
		while (curs->x + (len - curs->cursor) / w.ws_col > 0 && len > 0 && \
				curs->x + (len - curs->cursor) > w.ws_col)
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

static void	ft_suppr(t_cursor *curs, char *str)
{
	int	len;

	if (str[curs->cursor])
	{
		ft_printf("\033[s");
		ft_printf("\033[J");
		len = ft_strlen(str) - curs->cursor;
		ft_strlcpy(str + curs->cursor, str + curs->cursor + 1, len);
		ft_printf("%s", str + curs->cursor);
		ft_printf("\033[u");
	}
}

void	ft_escape(t_cursor *curs, size_t *moves, char **history)
{
	char	buff[1];
	size_t	prec_move;

	prec_move = *moves;
	if (read(0, ft_memset(buff, 0, 1), 1) == 1 && *buff == '[')
	{
		read(0, ft_memset(buff, 0, 1), 1);
		if (*buff == '3' && read(0, ft_memset(buff, 0, 1), 1) == 1 && \
			*buff == '~')
			ft_suppr(curs, history[split_len(history) - (*moves + 1)]);
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
