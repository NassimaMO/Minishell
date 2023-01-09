/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:18:37 by nghulam-          #+#    #+#             */
/*   Updated: 2022/08/09 18:18:39 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putstr_c(char *s, int len, int *count)
{
	if (len > (int)ft_strlen(s))
		len = ft_strlen(s);
	write(1, s, len);
	if (count && *count != -1)
		(*count) += len;
}

void	ft_putchar_count(char c, int *count)
{
	write(1, &c, 1);
	if (count && *count != -1)
		(*count)++;
}

void	print_chars(char c, int n, int *count)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar_count(c, count);
		i++;
	}
}

void	print_invalid(t_data_arg *data, char *str, int *count)
{
	if (*specif(str) == 'm')
		return (putstr_c("Success", 7, count));
	ft_putchar_count('%', count);
	if (have_flag(str, '#'))
		ft_putchar_count('#', count);
	if (have_flag(str, '+'))
		ft_putchar_count('+', count);
	else if (have_flag(str, '+'))
		ft_putchar_count('+', count);
	if (have_flag(str, '-'))
		ft_putchar_count('-', count);
	if (get_num(str, data, &first_num))
		ft_putnbr_base(get_num(str, data, &first_num), "0123456789", count);
	if (*flag(str) != '.' && flag(str) != specif(str))
		putstr_c(flag(str), last_num(str) - flag(str), count);
	else if (have_flag(str, '.'))
		ft_putchar_count('.', count);
	if (get_num(str, data, &last_num))
		ft_putnbr_base(get_num(str, data, &last_num), "0123456789", count);
	if (*specif(str) && *specif(str) != 'h' && *specif(str) != 'l')
		ft_putchar_count(*specif(str), count);
}

void	print_arg(t_data_arg *data, char *str, char c, int *count)
{
	if (c == 'c')
		return (ft_putchar_count(data->arg_int, count));
	if ((c == 'i' || c == 'd') && !last_num_null(data, str))
		return (ft_putnbr_base(data->arg_int, "0123456789", count));
	if ((c == 'u') && !last_num_null(data, str))
		return (ft_putnbr_base_u(data->arg_u, "0123456789", count));
	if (c == 's' && !data->arg_str && !not_printed_chain(data, str))
		return (putstr_c("(null)", 6, count));
	else if (c == 's' && have_flag(str, '.') && cut_chain(data, str))
		return (putstr_c(data->arg_str, get_num(str, data, last_num), count));
	if (c == 's')
		return (putstr_c(data->arg_str, ft_strlen(data->arg_str), count));
	if (c == '%')
		return (ft_putchar_count('%', count));
	if (c == 'p' && !data->arg_lu)
		return (putstr_c("(nil)", 5, count));
	if (c == 'p' && !incoming_format(data, str, &first_num))
		putstr_c("0x", 2, count);
	if (c == 'p')
		return (ft_putnbr_base_u(data->arg_lu, "0123456789abcdef", count));
	if ((c == 'x' && !last_num_null(data, str)))
		return (ft_putnbr_base_u(data->arg_u, "0123456789abcdef", count));
	if ((c == 'X') && !last_num_null(data, str))
		return (ft_putnbr_base_u(data->arg_u, "0123456789ABCDEF", count));
}
