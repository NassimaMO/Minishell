/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:20:36 by nghulam-          #+#    #+#             */
/*   Updated: 2022/08/09 18:20:38 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	sharp_bonus(t_data_arg *data, char *str, int *count)
{
	if (!have_flag(str, '#'))
		return ;
	if (*specif(str) == 'x' && data->arg_u)
		putstr_c("0x", 2, count);
	if (*specif(str) == 'X' && data->arg_u)
		putstr_c("0X", 2, count);
}

void	plus_bonus(t_data_arg *data, char *str, int *count)
{
	if (!have_flag(str, '+'))
		return ;
	if ((*specif(str) == 'd' || *specif(str) == 'i') && data->arg_int >= 0)
		return (ft_putchar_count('+', count));
	if (*specif(str) == 'p' && !null_arg(str, data))
		return (ft_putchar_count('+', count));
}

void	space_bonus(t_data_arg *data, char *str, int *count)
{
	if (!have_flag(str, ' ') || have_flag(str, '+'))
		return ;
	if ((*specif(str) == 'd' || *specif(str) == 'i') && data->arg_int >= 0)
		return (ft_putchar_count(' ', count));
}

void	dot_bonus(t_data_arg *data, char *str, int *count, int *shift)
{
	if (!have_flag(str, '.'))
		return ;
	if (last_num(str) && incoming_format(data, str, &first_num))
	{
		if (!*shift && shift_minus(data, str, &last_num))
			*shift = (ft_putchar_count('-', count), 1);
		flag_num(data, str, count, &last_num);
	}
}

void	minus_bonus(t_data_arg *data, char *str, int *count)
{
	int	shift;

	shift = 0;
	bonus_funct(data, str, count, &shift);
	if (shift)
		ft_putnbr_base_u((unsigned)(-1 * data->arg_int), "0123456789", count);
	else
		print_arg(data, str, *specif(str), count);
	if (first_num(str))
		flag_num(data, str, count, &first_num);
}
