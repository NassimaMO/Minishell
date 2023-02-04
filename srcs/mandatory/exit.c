/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:52:03 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/03 16:48:43 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_into_int(char *s, void *ptr, int size, int p)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ft_isdigit(s[i]))
	{
		n *= 10;
		n += s[i] - '0';
		i++;
	}
	if (s[i])
		return (-1);
	if (size == sizeof(char))
		*(char *)ptr = (char)(p * n);
	if (size == sizeof(int))
		*(int *)ptr = (int)(p * n);
	if (size == sizeof(long))
		*(long *)ptr = (long)(p * n);
	return (0);
}

int	ft_atoi_error(const char *s, void *n, int size)
{
	int	i;
	int	p;

	i = 0;
	p = 1;
	if (s[i] == '-' && ++i)
		p = -1;
	else if (s[i] == '+')
		i++;
	if (!ft_isdigit(s[i]))
		return (-1);
	return (str_into_int((char *)s + i, n, size, p));
}

int	check_exit(char *input, int *exit_code)
{
	char	*cmd;

	if (!input)
		return (ft_printf("\nexit\n"), EXIT);
	cmd = ft_strtrim(input, " \t");
	if (!ft_strncmp(input, "exit", 4))
	{
		ft_printf("exit\n");
		if (ft_strchr(cmd, ' '))
		{
			input = ft_strtrim(ft_strchr(cmd, ' '), " \t");
			if (ft_strchr(input, ' '))
			{
				*exit_code = (free(input), free(cmd), 1);
				return (ft_printf("exit: %s\n", S2ARG), 0);
			}
			if (ft_atoi_error(input, exit_code, sizeof(char)) < 0)
				*exit_code = (ft_printf("exit: %s: %s\n", input, SNUM), 2);
			free(input);
		}
		return (free(cmd), EXIT);
	}
	return (free(cmd), 0);
}
