/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:48:26 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/20 10:48:28 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	nb_number_type(t_data_arg *data, char c, int base)
{
	t_type	t;
	int		i;

	if (c == 'i')
		t.i = data->arg_int;
	if (c == 'u')
		t.u = data->arg_u;
	if (c == 'p')
		t.lu = data->arg_lu;
	if ((c == 'i' && !t.i) || (c == 'p' && !t.lu) || (c == 'u' && !t.u))
		return (1);
	i = 0;
	while ((c == 'i' && t.i) || (c == 'p' && t.lu) || (c == 'u' && t.u))
	{
		if (c == 'i')
			t.i = t.i / base;
		if (c == 'u')
			t.u = t.u / base;
		if (c == 'p')
			t.lu = t.lu / base;
		i++;
	}
	return (i);
}

void	ft_putnbr_base(int nbr, char *base, int *count)
{
	long long int	nb;

	nb = nbr;
	if (nb < 0)
	{
		ft_putchar_count('-', count);
		nb = -nb;
	}
	return (ft_putnbr_base_u(nb, base, count));
}

void	ft_putnbr_base_u(unsigned long int nbr, char *base, int *count)
{
	unsigned long int	n;

	n = ft_strlen(base);
	if (nbr < n)
		return (ft_putchar_count(base[nbr], count));
	if (nbr > n - 1)
	{
		ft_putnbr_base_u(nbr / n, base, count);
		ft_putchar_count(base[nbr % n], count);
	}
}

static int	str_into_int(char *nptr)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		if (n != 0)
			n *= 10;
		n += nptr[i] - '0';
		i++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	p;

	i = 0;
	p = 1;
	if (nptr[i] == '-')
	{
		p = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (0);
	return (p * str_into_int((char *)nptr + i));
}
