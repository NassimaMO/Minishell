/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/03 17:24:29 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	place_cursor(char *str, size_t cursor)
{
	size_t	i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len - cursor)
	{
		ft_printf("\033[1D");
		i++;
	}
}

static void	ft_escape(size_t *cursor, size_t *moves, char **history)
{
	char	buff[1];

	if (read(0, ft_memset(buff, 0, 1), 1) == 1 && *buff == '[')
	{
		printf("[%ld]\n", *moves);
		read(0, ft_memset(buff, 0, 1), 1);
		if ((*buff == 'C' && *cursor < ft_strlen(history[split_len(history) - (*moves + 1)]) && ++(*cursor)) || \
			(*buff == 'D' && *cursor > 0 && (--(*cursor), 1)))
			ft_printf("\033[1%c", *buff);
		if (history && ((*buff == 'A' && *moves < split_len(history) && \
		++(*moves)) || (*buff == 'B' && *moves > 0 && (--(*moves), 1))))
		{
			ft_printf("\33[2K\r");
			print_shell();
			ft_printf("%s", history[split_len(history) - (*moves + 1)]);
		}
	}
}

static char	*add_char(char *str, char c, size_t cursor)
{
	char	*new_str;

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

	ft_printf("\033[1D\033[K%s", str + (*cursor));
	place_cursor(str, (*cursor)--);
	len = ft_strlen(str) - (*cursor) + 1;
	ft_strlcpy(str + (*cursor), str + (*cursor) + 1, len);
}

char	*get_input(char **history)
{
	char	*str;
	char	buff[1];
	int		bytes;
	size_t	cursor;
	size_t	moves;

	bytes = read(0, ft_memset(buff, 0, 1), 1);
	history = add_split(history, "");
	ft_bzero((ft_bzero(&cursor, sizeof(size_t)), &moves), sizeof(size_t));
	while (history[split_len(history) - (moves + 1)] && bytes >= 0 && *buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 4) && !*history[split_len(history) - (moves + 1)])
			return (free_split(history), NULL);
		if (*buff == 27)
			ft_escape(&cursor, &moves, history);
		else if (*buff == 127 && cursor > 0)
			ft_del(&cursor, history[split_len(history) - (moves + 1)]);
		else if (ft_isprint(*buff))
			history[split_len(history) - (moves + 1)] = (ft_printf("%c%s", *buff, history[split_len(history) - (moves + 1)] + cursor), \
			place_cursor(history[split_len(history) - (moves + 1)], cursor), add_char(history[split_len(history) - (moves + 1)], *buff, cursor++));
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	if (bytes < 0 && *buff == 0)
		return (ft_printf("\n"), free_split(history), ft_strdup(""));
	str = history[split_len(history) - (moves + 1)];
	free_split(history);
	return (ft_printf("\n"), str);
}
