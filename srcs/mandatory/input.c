/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/11 06:51:05 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char			*str;
	char			buff[BUFFER_SIZE];
	int				bytes;

	bytes = read(0, ft_memset(buff, 0, BUFFER_SIZE), BUFFER_SIZE);
	str = ft_strdup(buff);
	while (str && bytes >= 0 && !ft_strchr(buff, '\n'))
	{
		if (bytes == 0 && !*str)
			return (free(str), NULL);
		bytes = read(0, ft_memset(buff, 0, BUFFER_SIZE), BUFFER_SIZE);
		str = gnl_join(str, buff, BUFFER_SIZE);
	}
	if (str)
		*ft_strchr(str, '\n') = 0;
	return (str);
}

int	check_exit(char *input)
{
	if (!input)
	{
		printf("\nexit\n");
		return (EXIT);
	}
	if (!ft_strncmp(input, "exit", 4))
	{
		printf("exit\n");
		free(input);
		return (EXIT);
	}
	return (0);
}
