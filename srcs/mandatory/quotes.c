/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:23:10 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/12 13:30:10 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_variable(char *input, int *x)
{
	char	*variable;
	char	*to_return;

	while (input[*x] && (ft_isalpha(input[*x]) || input[*x] == '_'))
		(*x)++;
	variable = malloc(sizeof(char) * (*x + 1));
	*x = 0;
	while (input[*x] && (ft_isalpha(input[*x]) || input[*x] == '_'))
	{
		variable[*x] = input[*x];
		(*x)++;
	}
	variable[*x] = '\0';
	to_return = getenv(variable);
	free(variable);
	if (!to_return)
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
	if (!*variable_tmp && (!input[*i] || input[*i] == ' '))
		*to_return = gnl_join(*to_return, "$", 1);
	else if (*variable_tmp)
		*to_return = gnl_join(*to_return, *variable_tmp, \
			ft_strlen(*variable_tmp));
	*i += x;
}

static void	go_through_input(char *input, char **to_return, int *i, char quotes)
{
	int			x;
	char		*variable_tmp;

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

static void	ft_quotes(char *quotes, char *input, int *i)
{
	while (input[*i] && (input[*i] == '\'' || input[*i] == '\"'))
	{
		if (!(*quotes))
			*quotes = input[(*i)++];
		else if (input[*i] == *quotes)
			*quotes = ((*i)++, '\0');
		else
			break ;
	}
}

void	quote_gestion(char *input, char **output, int exit_code)
{
	static char	quotes;
	char		*code;
	int			i;

	i = 0;
	while (input[i] && input[i] != ' ')
	{
		ft_quotes(&quotes, input, &i);
		if (input[i] && input[i] == '$' && input[i + 1] == '?')
		{
			code = ft_itoa(exit_code);
			*output = gnl_join(*output, code, ft_strlen(code));
			i += 2;
			free(code);
		}
		else
			go_through_input(input, output, &i, quotes);
	}
	if (input[i] && input[i] == ' ' && ((!*output[0] && quotes) || *output[0]))
		*output = gnl_join(*output, input + i++, 1);
	while (input[i] && input[i] == ' ' && !quotes)
		i++;
	if (quotes && !input[i])
		quotes = '\0';
	if (input[i])
		quote_gestion(input + i, output, exit_code);
}
