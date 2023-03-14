/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:02:58 by nghulam-          #+#    #+#             */
/*   Updated: 2022/08/23 16:03:00 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define BS BUFFER_SIZE

/* get_next_line.c */
char	*get_next_line(int fd);

/* get_next_line_utils.c */
char	*gnl_join(char *dest, char *src, int len);
char	*init(char *str, int len);
int		gnl_close(int fd);
size_t	gnl_strlen(const char *str);

#endif
