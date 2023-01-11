/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:01:47 by nghulam-          #+#    #+#             */
/*   Updated: 2022/08/23 16:01:49 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*readline(int fd, int reset)
{
	static char	buf[FOPEN_MAX][BS + 1];
	char		*s;

	s = ft_strdup(buf[fd]);
	if (!s || (reset && (free(s), reset)))
		return (init(buf[fd], BS), NULL);
	if (ft_strchr(s, '\n') && (init(ft_strchr(s, '\n') + 1, 0)))
		return (ft_strlcpy(buf[fd], ft_strchr(buf[fd], '\n') + 1, BS), s);
	while (read(fd, init(buf[fd], BS), BS) == BS && !ft_strchr(buf[fd], '\n'))
		s = gnl_join(s, buf[fd], BS);
	if (!*buf[fd] && !*s)
		return (free(s), NULL);
	if (ft_strchr(buf[fd], '\n'))
	{
		s = gnl_join(s, buf[fd], BS - ft_strlen(ft_strchr(buf[fd], '\n') + 1));
		ft_strlcpy(buf[fd], ft_strchr(buf[fd], '\n') + 1, BS);
	}
	else
	{
		s = gnl_join(s, buf[fd], ft_strlen(buf[fd]));
		init(buf[fd], BS);
	}
	if (ft_strchr(s, '\n'))
		init(ft_strchr(s, '\n') + 1, 0);
	return (s);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	return (readline(fd, 0));
}
