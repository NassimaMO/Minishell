/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:52:03 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/05 15:16:29 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_into_int(char *s, void *ptr, int size, int p)
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

static int	ft_atoi_error(const char *s, void *n, int size)
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
	char	**args;

	if (!input)
		return (ft_printf("\nexit\n"), EXIT);
	args = process_args(get_cmd_args(input), *exit_code);
	if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
	{
		ft_printf("exit\n");
		if (split_len(args) > 2)
			*exit_code = 1;
		if (split_len(args) > 2)
			return (print_err("exit", S2ARG), free_split(args), 0);
		if (split_len(args) > 1 && (ft_atoi_error(args[1], exit_code, sizeof(char)) < 0))
			*exit_code = (ft_printf("exit: %s: %s\n", input, SNUM), 2);
		return (free_split(args), EXIT);
	}
	return (free_split(args), 0);
}
