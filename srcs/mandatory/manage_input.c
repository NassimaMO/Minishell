/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:46:09 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/15 17:09:51 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_move(t_cursor *curs, char direction, int n)
{
	struct winsize	w;
	int				i;

	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	while (i < n)
	{
		if (direction == LEFT && curs->x == 1)
			ft_printf("\033[A\033[%dG", w.ws_col);
		else if (direction == RIGHT && curs->x == w.ws_col)
			ft_printf("\033[B\033[1G");
		else if (direction == LEFT)
			ft_printf("\033[D");
		else if (direction == RIGHT)
			ft_printf("\033[C");
		change_curs(curs, direction, 1);
		i++;
	}
}

char	*add_char_str(char *str, t_cursor *curs, char c)
{
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 2);
	ft_strlcpy(new_str, str, curs->cursor + 1);
	new_str[curs->cursor] = c;
	ft_strlcpy(new_str + curs->cursor + 1, str + curs->cursor, \
	ft_strlen(str + curs->cursor) + 1);
	free(str);
	return (new_str);
}

static char	*add_char(t_cursor *curs, char *str, char c)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	ft_printf("%c", c);
	if (curs->x == w.ws_col && curs->y == w.ws_row)
		curs->x = (ft_printf("\n"), 1);
	else if (curs->x == w.ws_col)
		ft_move(curs, RIGHT, 1);
	else
		change_curs(curs, RIGHT, 1);
	ft_printf("%s", str + curs->cursor);
	change_curs(curs, RIGHT, ft_strlen(str + curs->cursor));
	if (ft_strlen(str + curs->cursor) && curs->x == 1)
	{
		change_curs(curs, LEFT, 1);
		if (curs->y == w.ws_row)
			curs->x = (ft_printf("\n"), 1);
		else
			ft_move(curs, RIGHT, 1);
	}
	ft_move(curs, LEFT, ft_strlen(str + curs->cursor));
	return (add_char_str(str, curs, c));
}

static void	ft_del(t_cursor *curs, char *str)
{
	int	len;

	ft_move(curs, LEFT, 1);
	ft_printf("\033[s\033[J%s", str + curs->cursor);
	ft_printf("\033[u");
	curs->cursor--;
	len = ft_strlen(str) - curs->cursor;
	ft_strlcpy(str + curs->cursor, str + curs->cursor + 1, len);
}

void	process_input(char **history, char *buff, size_t *moves, t_cursor *curs)
{
	if (*buff == 27)
		ft_escape(curs, moves, history);
	else if (*buff == 127 && curs->cursor > 0)
		ft_del(curs, history[split_len(history) - (*moves + 1)]);
	else if (ft_isprint(*buff))
	{
		history[split_len(history) - (*moves + 1)] = \
		add_char(curs, history[split_len(history) - (*moves +1)], *buff);
		curs->cursor++;
	}
}
