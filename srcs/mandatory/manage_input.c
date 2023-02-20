/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:46:09 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/15 09:44:00 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_move(char direction, int n)
{
	struct winsize	w;
	int				i;
	int				x;
	int				y;

	i = 0;
	get_cursor_pos((ioctl(0, TIOCGWINSZ, &w), &x), &y);
	while (i < n)
	{
		if (direction == LEFT && (x % w.ws_col) == 1)
		{
			ft_printf("\033[A\033[%dG", w.ws_col);
			x = w.ws_col;
		}
		else if (direction == RIGHT && x % w.ws_col == 0)
			x = (ft_printf("\033[B\r"), 1);
		else if (direction == LEFT)
			ft_printf((x--, "\033[D"));
		else if (direction == RIGHT)
			ft_printf((x++, "\033[C"));
		i++;
	}
}

static void	ft_escape(size_t *cursor, size_t *moves, char **history)
{
	char	buff[1];
	size_t	prec_move;

	prec_move = *moves;
	if (read(0, ft_memset(buff, 0, 1), 1) == 1 && *buff == '[')
	{
		read(0, ft_memset(buff, 0, 1), 1);
		if ((*buff == 'C' && *cursor < ft_strlen(history[split_len(history) - \
			(*moves + 1)]) && ++(*cursor)) || \
			(*buff == 'D' && *cursor > 0 && (--(*cursor), 1)))
			ft_move(*buff, 1);
		if (history && ((*buff == 'A' && *moves < split_len(history) && \
		++(*moves)) || (*buff == 'B' && *moves > 0 && (--(*moves), 1))))
			go_through_hist(cursor, moves, history, \
			ft_strlen(history[split_len(history) - (prec_move + 1)]));
	}
}

static char	*add_char(char *str, char c, size_t cursor)
{
	char			*new_str;
	int				x;
	int				y;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	get_cursor_pos(&x, &y);
	ft_printf("%c", c);
	if (x == w.ws_col)
	{
		if (y == w.ws_row)
			ft_printf("\n");
		ft_move(RIGHT, 1);
	}
	get_cursor_pos(&x, &y);
/* 	if (x == w.ws_col)
	{
		x = 0;
		if (y == w.ws_row)
			ft_printf("\n");
		else
			y++;
	}
	else
		x++; */
	ft_printf("%s", str + cursor);
	ft_printf("\033[%d;%dH", y, x);
	new_str = malloc(ft_strlen(str) + 2);
	ft_strlcpy(new_str, str, cursor + 1);
	new_str[cursor] = c;
	ft_strlcpy(new_str + cursor + 1, str + cursor, ft_strlen(str + cursor) + 1);
	return (free(str), new_str);
}

static void	ft_del(size_t *cursor, char *str)
{
	int	len;

	ft_move(LEFT, 1);
	ft_printf("\033[s\033[J%s", str + (*cursor));
	ft_printf("\033[u");
	(*cursor)--;
	len = ft_strlen(str) - (*cursor);
	ft_strlcpy(str + (*cursor), str + (*cursor) + 1, len);
}

void	process_input(char **history, char *buff, size_t *moves, size_t *cursor)
{
	if (*buff == 27)
		ft_escape(cursor, moves, history);
	else if (*buff == 127 && *cursor > 0)
		ft_del(cursor, history[split_len(history) - (*moves + 1)]);
	else if (ft_isprint(*buff))
		history[split_len(history) - (*moves + 1)] = \
		add_char(history[split_len(history) - (*moves +1)], *buff, (*cursor)++);
}
