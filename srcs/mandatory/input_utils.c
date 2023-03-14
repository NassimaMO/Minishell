/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 14:21:08 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_trim_but_no(char *str, char c)
{
	char	*to_return;
	int		i;
	int		j;

	i = 0;
	j = 0;
	to_return = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			if (!str[i])
				break ;
			if (j)
				to_return[j++] = c;
		}
		to_return[j++] = str[i];
		i++;
	}
	return (to_return);
}

static char	*get_variable(char *input, int *x)
{
	char	*variable;
	char	*to_return;

	if (ft_isdigit(input[*x]) && *x == 0)
		return ((*x)++, NULL);
	while (input[*x] && (ft_isalpha(input[*x]) || input[*x] == '_' \
			|| ft_isdigit(input[*x])))
		(*x)++;
	variable = malloc(sizeof(char) * (*x + 1));
	*x = 0;
	while (input[*x] && (ft_isalpha(input[*x]) || input[*x] == '_' \
			|| ft_isdigit(input[*x])))
	{
		variable[*x] = input[*x];
		(*x)++;
	}
	variable[*x] = '\0';
	to_return = getenv(variable);
	if ((free(variable), 1) && !to_return)
		return (NULL);
	return (to_return);
}

static void	variable_gestion(char *input, char **to_return, \
								char quotes, int *i)
{
	int		x;
	char	*variable_tmp;

	x = 0;
	if (input[++(*i)] == '\"' || input[*i] == '\'')
		return ;
	variable_tmp = get_variable(input + *i, &x);
	if (variable_tmp && !quotes)
		variable_tmp = str_trim_but_no(variable_tmp, ' ');
	if (!variable_tmp && (!input[*i] || input[*i] == ' ' || x == 0))
		*to_return = gnl_join(*to_return, "$", 1);
	else if (variable_tmp)
		*to_return = gnl_join(*to_return, variable_tmp, \
			ft_strlen(variable_tmp));
	if (variable_tmp && !quotes)
		free(variable_tmp);
	*i += x;
}

void	go_through_input(char *input, char **to_return, int *i, char quotes)
{
	int		x;
	char	*variable_tmp;

	x = 0;
	if (input[*i] && input[*i] == '$' && \
		((quotes == '\"' && input[*i + 1] != '\"') || !quotes))
		variable_gestion(input, to_return, quotes, i);
	else if (input[*i] && input[*i] == '~' && (!input[*i + 1] \
			|| input[*i + 1] == '/' || input[*i + 1] == ':' \
			|| input[*i + 1] == ' ') && (*i == 0 || \
			input[*i - 1] == ' '))
	{
		variable_tmp = get_variable("HOME", &x);
		if (variable_tmp)
			*to_return = gnl_join(*to_return, variable_tmp, \
				ft_strlen(variable_tmp));
		(*i)++;
	}
	else if (input[*i])
		*to_return = gnl_join(*to_return, input + (*i)++, 1);
}

void	get_cursor_pos(int *x, int *y)
{
	char	*str;
	char	c;

	*x = print_shell(LEN);
	*y = 1;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return ;
	write(1, "\033[6n", 4);
	str = NULL;
	while (read(0, &c, 1) > 0 && c != 'R')
		str = gnl_join(str, &c, 1);
	if (ft_strchr(str, '['))
		*y = ft_atoi(ft_strchr(str, '[') + 1);
	if (ft_strchr(str, ';'))
		*x = ft_atoi(ft_strchr(str, ';') + 1);
	free(str);
}
