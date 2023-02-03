/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/02 13:40:24 by nmouslim         ###   ########.fr       */
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

static void	ft_escape(size_t *cursor, size_t *moves, char **str, char **history)
{
	char	buff[1];

	if (read(0, ft_memset(buff, 0, 1), 1) == 1 && *buff == '[')
	{
		read(0, ft_memset(buff, 0, 1), 1);
		if ((*buff == 'C' && *cursor < ft_strlen(*str) && ++(*cursor)) || \
			(*buff == 'D' && *cursor > 0 && (--(*cursor), 1)))
			ft_printf("\033[1%c", *buff);
		if (history && ((*buff == 'A' && *moves < split_len(history) && \
		++(*moves)) || (*buff == 'B' && *moves > 0 && (--(*moves), 1))))
		{
			ft_printf("\33[2K\r");
			print_shell();
			if (*moves == 0)
				ft_printf("%s", *str);
			else
				ft_printf("%s", history[split_len(history) - *moves]);
			//str
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

char	*get_input(char ***history)
{
	char	*str;
	char	buff[1];
	int		bytes;
	size_t	cursor;
	size_t	moves;

	bytes = read(0, ft_memset(buff, 0, 1), 1);
	str = ft_strdup("");
	ft_bzero((ft_bzero(&cursor, sizeof(size_t)), &moves), sizeof(size_t));
	while (str && bytes >= 0 && *buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 4) && !*str)
			return (free(str), NULL);
		if (*buff == 27)
			ft_escape(&cursor, &moves, &str, *history);
		else if (*buff == 127 && cursor > 0)
			ft_del(&cursor, str);
		else if (ft_isprint(*buff))
			str = (ft_printf("%c%s", *buff, str + cursor), \
			place_cursor(str, cursor), add_char(str, *buff, cursor++));
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	if (bytes < 0 && *buff == 0)
		return (ft_printf("\n"), free(str), ft_strdup(""));
	*history = add_split(*history, ft_strdup(str));
	return (ft_printf("\n"), str);
}
