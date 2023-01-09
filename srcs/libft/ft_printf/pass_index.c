/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:08:39 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/24 18:08:41 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*first_num(char *str)
{
	while (*str == '-' || *str == '0' || *str == '+' || *str == ' ' || \
	*str == '#')
		str ++;
	return (str);
}

char	*flag(char *str)
{
	str = first_num(str);
	if (('1' <= *str && *str <= '9') || *str == '*')
	{
		str ++;
		while ('0' <= *str && *str <= '9')
			str ++;
	}
	return (str);
}

char	*last_num(char *str)
{
	str = flag(str);
	while (*str == '+' || *str == '-' || *str == ' ' || *str == '.' \
	|| *str == '#' || *str == '0')
		str ++;
	return (str);
}

char	*specif(char *str)
{
	str = last_num(str);
	while (('0' <= *str && *str <= '9') || *str == '*')
		str ++;
	return (str);
}

int	pass_index(char *str)
{
	if (specif(str) >= str)
		return ((specif(str) + 1) - str);
	return (1);
}
