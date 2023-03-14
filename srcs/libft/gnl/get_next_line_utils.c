/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:54:11 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 14:27:03 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*init(char *str, int len)
{
	int	i;

	i = 0;
	if (!len)
		len = ft_strlen(str);
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*gnl_join(char *dest, char *src, int len)
{
	char	*new_dest;

	if (len < 0)
		len = ft_strlen(src);
	new_dest = malloc(ft_strlen(dest) + len + 1);
	ft_strlcpy(new_dest, dest, ft_strlen(dest) + 1);
	ft_strlcpy(new_dest + ft_strlen(dest), src, len + 1);
	free(dest);
	return (new_dest);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 0 && str[i - 1] == '\n')
		i--;
	return (i);
}

/* int	gnl_close(int fd)
{
	return (readline(fd, 1), close(fd));
} */
