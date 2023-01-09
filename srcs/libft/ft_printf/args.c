/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:12:53 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/24 18:12:55 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	str_arg_i(va_list args, t_data_arg *data, char c, char *str)
{
	data->arg_int = va_arg(args, int);
	if (c == 'c')
		data->len = 1;
	else if (c == 'i' || c == 'd')
	{
		if (!data->arg_int && have_flag(str, '.') && \
		!get_num(str, data, last_num))
			data->len = 0;
		else
			data->len = nb_number_type(data, 'i', 10);
	}
}

static void	str_arg_s(va_list args, t_data_arg *data, char *str)
{
	int	num;

	data->arg_str = va_arg(args, char *);
	data->len = ft_strlen(data->arg_str);
	if (*specif(str) == 's' && have_flag(str, '.') && data->arg_str)
	{
		num = get_num(str, data, &last_num);
		if ((*last_num(str) != '*' || data->last_n >= 0) && num < data->len)
			data->len = num;
	}
	else if (!data->arg_str)
	{
		if (have_flag(str, '.') && get_num(str, data, &last_num) < 6)
			data->len = 0;
		else
			data->len = ft_strlen("(null)");
	}
}

static void	str_arg_u(va_list args, t_data_arg *data, char c, char *str)
{
	data->arg_u = va_arg(args, unsigned int);
	if (c == 'u')
		data->len = nb_number_type(data, 'u', 10);
	if (c == 'x' || c == 'X')
		data->len = nb_number_type(data, 'u', 16);
	if (!data->arg_u && have_flag(str, '.') && !get_num(str, data, last_num))
		data->len = 0;
}

static void	str_arg_p(va_list args, t_data_arg *data)
{
	data->arg_lu = va_arg(args, unsigned long);
	if (data->arg_lu)
		data->len = nb_number_type(data, 'p', 16) + 2;
	else
		data->len = ft_strlen("(nil)");
}

void	get_args(va_list args, char *str, t_data_arg *data, int *count)
{
	char	c;

	asterisk(args, str, data);
	c = *(specif(str));
	if (c == 's')
		str_arg_s(args, data, str);
	else if (c == 'd' || c == 'i' || c == 'c')
		str_arg_i(args, data, c, str);
	else if (c == 'u' || c == 'x' || c == 'X')
		str_arg_u(args, data, c, str);
	else if (c == 'p')
		str_arg_p(args, data);
	else if (c == '%')
		data->len = 1;
	else if (!c)
		*count = -1;
}
