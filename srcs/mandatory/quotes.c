/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:23:10 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/04 18:19:48 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable(char *input, int *x)
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

void	go_through_input(char *input, char **to_return, int *i, char quotes)
{
	int			x;
	char		*variable_tmp;

	x = 0;
	if (input[*i] && input[*i] == '$' && \
		((quotes == '\"' && input[*i + 1] != '\"') || !quotes))
	{
		variable_tmp = ((*i)++, get_variable(input + *i, &x));
		if (!variable_tmp && (!input[*i] || input[*i] == ' '))
			*to_return = gnl_join(*to_return, "$", 1);
		else if (variable_tmp)
			*to_return = gnl_join(*to_return, variable_tmp, \
				ft_strlen(variable_tmp));
		*i += x;
	}
	else if (input[*i] && input[*i] == '~' && (!input[*i + 1] \
			|| input[*i + 1] == '/' || input[*i + 1] == ':' \
			|| input[*i + 1] == ' '))
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

int	quote_gestion(char *input, char **output, int i, int exit_code)
{
	static char	quotes;
	char		*code;

	*output = ft_strdup("");
	while (input[i] && input[i] != ' ')
	{
		while (input[i] && (input[i] == '\'' || input[i] == '\"'))
		{
			if (!quotes)
				quotes = input[i++];
			else if (input[i] == quotes)
				quotes = (i++, '\0');
			else
				break ;
		}
		if (input[i] && input[i] == '$' && input[i + 1] == '?')
		{
			code = ft_itoa(exit_code);
			*output = (i += 2, gnl_join(*output, code, ft_strlen(code)));
			free(code);
		}
		else
			go_through_input(input, output, &i, quotes);
	}
	if (quotes && !input[i])
		quotes = '\0';
	return (i);
}
