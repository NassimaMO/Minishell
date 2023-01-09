/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:27:13 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/24 12:27:15 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int					count;
	long unsigned int	i;
	va_list				args;
	t_data_arg			data;

	count = 0;
	i = 0;
	va_start(args, str);
	while (i < ft_strlen(str))
	{
		while (str[i] && str[i] != '%')
			ft_putchar_count(str[i++], &count);
		if (i++ < ft_strlen(str))
		{
			format_print(args, (char *)str + i, &data, &count);
			i += pass_index((char *)str + i);
		}
	}
	return (va_end(args), count);
}
