/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:27:22 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/24 12:27:24 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>

# include "libft.h"

typedef union u_type {
	int				i;
	unsigned long	lu;
	unsigned int	u;
}	t_type;

typedef struct s_data_arg{
	union{
		char				*arg_str;
		int					arg_int;
		unsigned int		arg_u;
		long unsigned		arg_lu;
	};
	int		len;
	int		first_n;
	int		last_n;
}	t_data_arg;

/* args.c */

void	get_args(va_list args, char *str, t_data_arg *data, int *count);

/* conditions.c */

int		incoming_minus(t_data_arg *data, char *str, char *(num)(char *));
int		is_specif(char c);
int		shift_minus(t_data_arg *data, char *str, char *(num)(char *));
int		null_arg(char *str, t_data_arg *data);
int		invalid_flag(char *str);

/* bonus_conditions.c */

int		minus_bool(t_data_arg *data, char *str);
int		incoming_format(t_data_arg *data, char *str, char *(num)(char *));
int		incoming_0x(t_data_arg *data, char *str, char *(num)(char *));
int		cut_chain(t_data_arg *data, char *str);
int		not_printed_chain(t_data_arg *data, char *str);

/* bonus_func.c */

void	sharp_bonus(t_data_arg *data, char *str, int *count);
void	plus_bonus(t_data_arg *data, char *str, int *count);
void	space_bonus(t_data_arg *data, char *str, int *count);
void	dot_bonus(t_data_arg *data, char *str, int *count, int *shift);
void	minus_bonus(t_data_arg *data, char *str, int *count);

/* bonus_utils.c */

char	char_fill(t_data_arg *data, char *str, char *(num)(char *));
int		get_num(char *str, t_data_arg *data, char *(num)(char *));
int		last_num_null(t_data_arg *data, char *str);
void	asterisk(va_list args, char *str, t_data_arg *data);
int		prev_c(t_data_arg *data, char *str, char *(num)(char *));
/* main_file.c */

void	flag_num(t_data_arg *data, char *str, int *count, char	*(num)(char *));
void	bonus_funct(t_data_arg *data, char *str, int *count, int *shift);
int		have_flag(char *str, char flag);
void	format_print(va_list args, char *str, t_data_arg *data, int *count);

/* pass_index.c */

char	*first_num(char *str);
char	*flag(char *str);
char	*last_num(char *str);
char	*specif(char *str);
int		pass_index(char *str);

/* print.c*/

void	putstr_c(char *s, int len, int *count);
void	ft_putchar_count(char c, int *count);
void	print_chars(char c, int n, int *count);
void	print_invalid(t_data_arg *data, char *str, int *count);
void	print_arg(t_data_arg *data, char *str, char c, int *count);

/* utils.c */

int		nb_number_type(t_data_arg *data, char c, int base);
void	ft_putnbr_base(int nbr, char *base, int *count);
void	ft_putnbr_base_u(unsigned long int nbr, char *base, int *count);
int		ft_atoi(const char *nptr);

/* ft_printf.c */

int		ft_printf(const char *str, ...);

#endif
