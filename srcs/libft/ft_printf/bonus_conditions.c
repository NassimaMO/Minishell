/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:13:29 by nghulam-          #+#    #+#             */
/*   Updated: 2022/08/09 18:13:31 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	minus_bool(t_data_arg *data, char *str)
{
	if (have_flag(str, '-'))
		return (1);
	if (!have_flag(str, '*'))
		return (0);
	if (!get_num(str, data, &first_num))
		return (0);
	if (*first_num(str) != '*' || data->first_n >= 0)
		return (0);
	return (1);
}

int	incoming_format(t_data_arg *data, char *str, char	*(num)(char *))
{
	if (num != &first_num)
		return (0);
	if (*specif(str) == 's' || *specif(str) == 'c')
		return (0);
	if (!have_flag(str, '.') || (*last_num(str) == '*' && data->last_n < 0))
		return (0);
	if (get_num(str, data, &last_num) < (data->len - 2 * (*specif(str) == 'p')))
		return (0);
	if (*specif(str) == 'p' && null_arg(str, data))
		return (0);
	return (1);
}

int	incoming_0x(t_data_arg *data, char *str, char	*(num)(char *))
{
	if (num != &first_num)
		return (0);
	if (!have_flag(str, '#'))
		return (0);
	if ((*specif(str) != 'x' && *specif(str) != 'X'))
		return (0);
	if (null_arg(str, data))
		return (0);
	return (1);
}

int	cut_chain(t_data_arg *data, char *str)
{
	if (*specif(str) != 's' || !have_flag(str, '.'))
		return (0);
	if ((*last_num(str) == '*' && data->last_n < 0))
		return (0);
	return (1);
}

int	not_printed_chain(t_data_arg *data, char *str)
{
	if (*specif(str) != 's')
		return (0);
	if (!null_arg(str, data))
		return (0);
	if (!have_flag(str, '.'))
		return (0);
	if (get_num(str, data, &last_num) > 5)
		return (0);
	return (1);
}
