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
	char			buff[1];
	int				bytes;

	bytes = read(0, ft_memset(buff, 0, 1), 1);
	str = ft_strdup("");
	while (str && bytes >= 0 && *buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 3 || *buff == 4) && !*str)
			return (free(str), NULL);
		if (ft_isprint(*buff))
		{
			ft_printf("%c", *buff);
			str = gnl_join(str, buff, 1);
		}
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	if (*buff == '\n')
		ft_printf("\n");
	return (str);
}

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

int	check_exit(char *input)
{
	char	code;
	char	*cmd;

	if (!input)
		return (ft_printf("\nexit\n"), EXIT);
	cmd = ft_strtrim(input, " ");
	code = 0;
	if (!ft_strncmp(input, "exit", 4))
	{
		printf("exit\n");
		if (ft_strchr(cmd, ' '))
		{
			input = ft_strtrim(ft_strchr(cmd, ' '), " ");
			if (ft_strchr(input, ' '))
				return (ft_printf("exit: too many arguments\n"), \
				exit_code(SET, 1), free(input), free(cmd), 0);
			if (ft_atoi_error(input, &code, sizeof(char)) < 0)
				code = (ft_printf("exit: %s: numeric argument required\n"), 2);
			free(input);
		}
		return (free(cmd), exit_code(SET, code), EXIT);
	}
	return (free(cmd), 0);
}
