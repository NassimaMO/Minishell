/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:46:09 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/05 14:46:21 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_move(size_t cursor, char direction, int n)
{
	struct winsize	w;
	int				i;

	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	while (i < n)
	{
		if (direction == LEFT && !((cursor + print_shell(LEN) + 1) % w.ws_col))
			ft_printf("\033[A\033[%dG", w.ws_col);
		else if (direction == RIGHT && \
		(int)(cursor + print_shell(LEN) - 1) % w.ws_col == w.ws_col - 1)
			ft_printf("\033[B\r");
		else
			ft_printf("\033[%c", direction);
		if (direction == RIGHT)
			cursor++;
		else
			cursor--;
		i++;
	}
}

static void	ft_escape(size_t *cursor, size_t *moves, char **history)
{
	char	buff[1];

	if (read(0, ft_memset(buff, 0, 1), 1) == 1 && *buff == '[')
	{
		read(0, ft_memset(buff, 0, 1), 1);
		if ((*buff == 'C' && *cursor < ft_strlen(history[split_len(history) - \
			(*moves + 1)]) && ++(*cursor)) || \
			(*buff == 'D' && *cursor > 0 && (--(*cursor), 1)))
			ft_move(*cursor, *buff, 1);
		if (history && ((*buff == 'A' && *moves < split_len(history) && \
		++(*moves)) || (*buff == 'B' && *moves > 0 && (--(*moves), 1))))
		{
			if (split_len(history) >= (*moves + 1))
			{
				ft_printf("\033[u");
				ft_printf("\033[J\r");
				print_shell(0);
				ft_printf("%s", history[split_len(history) - (*moves + 1)]);
				*cursor = ft_strlen(history[split_len(history) - (*moves + 1)]);
			}
			else
				(*moves)--;
		}
	}
}

static char	*add_char(char *str, char c, size_t cursor)
{
	char	*new_str;

	ft_printf("%c%s", c, str + cursor);
	ft_move(ft_strlen(str), LEFT, ft_strlen(str) - cursor);
	new_str = malloc(ft_strlen(str) + 2);
	ft_strlcpy(new_str, str, cursor + 1);
	new_str[cursor] = c;
	ft_strlcpy(new_str + cursor + 1, str + cursor, ft_strlen(str + cursor) + 1);
	free(str);
	return (new_str);
}

static void	ft_del(size_t *cursor, char *str)
{
	int	len;

	ft_move(*cursor - 1, LEFT, 1);
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
