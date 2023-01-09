/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:17:49 by nghulam-          #+#    #+#             */
/*   Updated: 2022/08/09 18:17:50 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	incoming_minus(t_data_arg *data, char *str, char *(num)(char *))
{
	if (num != &first_num)
		return (0);
	if (*specif(str) != 'd' && *specif(str) != 'i')
		return (0);
	if (data->arg_int >= 0)
		return (0);
	return (1);
}

int	is_specif(char c)
{
	if (c != 'd' && c != 'i' && c != 'c' && c != 'u' && c != 'x' \
	&& c != 'X' && c != 'p' && c != 's' && c != '%')
		return (0);
	return (1);
}

int	shift_minus(t_data_arg *data, char *str, char	*(num)(char *))
{
	if (*specif(str) != 'd' && *specif(str) != 'i')
		return (0);
	if (data->arg_int >= 0)
		return (0);
	if (char_fill(data, str, num) != '0')
		return (0);
	return (1);
}

int	null_arg(char *str, t_data_arg *data)
{
	if ((*specif(str) == 'c' || *specif(str) == 'i' || *specif(str) == 'd') \
	&& !data->arg_int)
		return (1);
	if ((*specif(str) == 'u' || *specif(str) == 'x' || *specif(str) == 'X') \
	&& !data->arg_u)
		return (1);
	if (*specif(str) == 'p' && !data->arg_lu)
		return (1);
	if (*specif(str) == 's' && !data->arg_str)
		return (1);
	return (0);
}

int	invalid_flag(char *str)
{
	if (ft_strchr(str, ' ') && ft_strchr(str, ' ') < specif(str) && \
	!have_flag(str, ' '))
		return (1);
	if (ft_strchr(str, '+') && ft_strchr(str, '+') < specif(str) && \
	!have_flag(str, '+'))
		return (1);
	if (ft_strchr(str, '#') && ft_strchr(str, '#') < specif(str) && \
	!have_flag(str, '#'))
		return (1);
	return (0);
}
