/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:11:20 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/24 18:11:22 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	char_fill(t_data_arg *data, char *str, char *(num)(char *))
{
	if (num == &first_num && have_flag(str, '0') && \
	(*(first_num(str)) == '*' && data->first_n < 0))
		return (' ');
	if ((num == &last_num || (*flag(str) != '.' && \
	have_flag(str, '0'))) && *specif(str) != 's')
		return ('0');
	if (num == &first_num && have_flag(str, '0') && \
	(*(last_num(str)) == '*' && data->last_n < 0))
		return ('0');
	if (*specif(str) == 's' || num == &first_num)
		return (' ');
	return ('0');
}

int	get_num(char *str, t_data_arg *data, char	*(num)(char *))
{
	if (*(num(str)) == '*')
	{
		if (num == &first_num)
		{
			if (data->first_n < 0)
				return (-data->first_n);
			return (data->first_n);
		}
		if (data->last_n < 0)
			return (-1);
		return (data->last_n);
	}
	return (ft_atoi(num(str)));
}

int	last_num_null(t_data_arg *data, char *str)
{
	char	c;

	c = *specif(str);
	if (c != 'p' && null_arg(str, data))
	{
		if (have_flag(str, '.') && !get_num(str, data, &last_num))
			return (1);
	}
	return (0);
}

void	asterisk(va_list args, char *str, t_data_arg *data)
{
	if (*first_num(str) == '*')
		data->first_n = va_arg(args, int);
	if (*last_num(str) == '*')
		data->last_n = va_arg(args, int);
}

int	prev_c(t_data_arg *data, char *str, char *(num)(char *))
{
	if (num != &first_num)
		return (0);
	if ((*specif(str) == 'd' || *specif(str) == 'i') && \
	(have_flag(str, '+') || have_flag(str, ' ')))
		return (1);
	if (*specif(str) == 'p' && (have_flag(str, '+') || have_flag(str, ' ')) \
	&& !null_arg(str, data))
		return (1);
	return (0);
}
