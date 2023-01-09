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

void	flag_num(t_data_arg *data, char *str, int *count, char	*(num)(char *))
{
	int	n;

	n = get_num(str, data, num) - data->len;
	if (incoming_format(data, str, num))
		n -= get_num(str, data, &last_num) - \
		(data->len - 2 * (*specif(str) == 'p'));
	if (incoming_0x(data, str, num))
		n -= 2;
	if (incoming_minus(data, str, num) || prev_c(data, str, num))
		n--;
	if (*specif(str) == 'p' && num == &last_num)
		n += 2;
	if (n > 0)
	{
		if (*specif(str) == 'p' && num == &last_num)
			putstr_c("0x", 2, count);
		print_chars(char_fill(data, str, num), n, count);
	}
}

void	bonus_funct(t_data_arg *data, char *str, int *count, int *shift)
{
	sharp_bonus(data, str, count);
	plus_bonus(data, str, count);
	space_bonus(data, str, count);
	dot_bonus(data, str, count, shift);
}

int	have_flag(char *str, char flag)
{
	if (!ft_strchr(str, flag))
		return (0);
	if ((flag == '.') && ft_strchr(str, '.') <= last_num(str))
		return (1);
	if ((flag == '-' || flag == '+' || flag == ' ' || flag == '#' \
	|| flag == '0') && ft_strchr(str, flag) <= first_num(str))
		return (1);
	if (flag == '*' && ft_strchr(str, '*') <= specif(str))
		return (1);
	return (0);
}

void	format_print(va_list args, char *str, t_data_arg *data, int *count)
{
	char	c;
	int		shift;

	shift = 0;
	get_args(args, str, data, count);
	c = *specif(str);
	if (*specif(str) == '%')
		return (ft_putchar_count('%', count));
	if (!is_specif(c) || invalid_flag(str))
		return (print_invalid(data, str, count));
	if (minus_bool(data, str))
		return (minus_bonus(data, str, count));
	if (first_num(str))
	{
		if (!shift && shift_minus(data, str, &first_num))
			shift = (ft_putchar_count('-', count), 1);
		flag_num(data, str, count, &first_num);
	}
	bonus_funct(data, str, count, &shift);
	if (shift)
		ft_putnbr_base_u((unsigned)(-1 * data->arg_int), "0123456789", count);
	else
		print_arg(data, str, *specif(str), count);
}
