/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/14 15:18:18 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
								char **variable_tmp, int *i)
{
	int	x;

	x = 0;
	if (input[++(*i)] == '\"' || input[*i] == '\'')
		return ;
	*variable_tmp = get_variable(input + *i, &x);
	if (!*variable_tmp && (!input[*i] || input[*i] == ' ' || x == 0))
		*to_return = gnl_join(*to_return, "$", 1);
	else if (*variable_tmp)
		*to_return = gnl_join(*to_return, *variable_tmp, \
			ft_strlen(*variable_tmp));
	*i += x;
}

void	go_through_input(char *input, char **to_return, int *i, char quotes)
{
	int		x;
	char	*variable_tmp;

	x = 0;
	if (input[*i] && input[*i] == '$' && \
		((quotes == '\"' && input[*i + 1] != '\"') || !quotes))
		variable_gestion(input, to_return, &variable_tmp, i);
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

void	curs(size_t cursor, char *str)
{
	ft_move(cursor, RIGHT, ft_strlen(str) - cursor);
}

char	*get_input(char **history)
{
	char	*str;
	char	buff[1];
	int		bytes;
	size_t	cursor;
	size_t	moves;

	ft_printf((set_terminal(SET), "\033[s"));
	bytes = read(0, ft_memset(buff, 0, 1), 1);
	history = add_split(history, ft_strdup(""));
	ft_bzero((ft_bzero(&cursor, sizeof(size_t)), &moves), sizeof(size_t));
	while (history[split_len(history) - (moves + 1)] && bytes >= 0 && \
			*buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 4) && \
				!*history[split_len(history) - (moves + 1)])
			return (free_split(history), set_terminal(0), NULL);
		process_input(history, buff, &moves, &cursor);
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	if (bytes < 0 && *buff == 0)
		return (ft_printf("\n"), free_split(history), \
		set_terminal(RESET), ft_strdup(""));
	str = ft_strdup(history[split_len(history) - (moves + 1)]);
	free_split(history);
	return (curs(cursor, str), ft_printf("\n"), set_terminal(RESET), str);
}
