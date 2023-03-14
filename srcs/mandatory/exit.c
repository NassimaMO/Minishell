/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:52:03 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 14:16:22 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_into_int(char *s, void *ptr, size_t size, int p)
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

int	ft_atoi_err(const char *s, void *n, size_t size)
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

static int	check_overflow(char *s, long long max)
{
	size_t		i;
	long long	tmp;

	i = 1;
	tmp = max;
	while (((max >= 0 && tmp >= 10) || (max < 0 && tmp <= -10)) && i++)
		tmp /= 10;
	if ((max > 0 && *s == '-') || (max < 0 && *s != '-') || ft_strlen(s) < i)
		return (0);
	if (ft_strlen(s) - (*s == '-') > i)
		return (1);
	i = ft_strlen(s) - 1;
	while (1)
	{
		if ((max >= 0 && s[i] - '0' > max % 10) || \
			(max < 0 && s[i] - '0' > -(max % 10)))
			return (1);
		max /= 10;
		if (i == 0 || s[i - 1] == '-')
			break ;
		i--;
	}
	return (0);
}

int	check_exit(char *input)
{
	char	**args;

	set_terminal(SET);
	if (!input)
		return (ft_printf("\nexit\n"), set_terminal(RESET), EXIT);
	args = process_args(get_cmd_args(input));
	if (args && *args && !ft_strncmp(*args, "exit", 4) && ft_strlen(*args) == 4)
	{
		ft_printf("exit\n");
		if (split_len(args) > 1 && \
			(check_overflow(args[1], LLONG_MAX) || \
			check_overflow(args[1], LLONG_MIN) || \
			ft_atoi_err(args[1], &g_exit_code, 1) < 0))
			g_exit_code = (write(2, "exit: ", 6), print_err(args[1], SNUM), 2);
		else if (split_len(args) > 2)
		{
			g_exit_code = 1;
			return (print_err("exit", S2ARG), set_terminal(0), \
					free_split(args), 0);
		}
		return (free_split(args), set_terminal(RESET), EXIT);
	}
	return (free_split(args), set_terminal(RESET), 0);
}
