/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:23 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/28 14:19:28 by nmouslim         ###   ########.fr       */
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

static void	print_variable(char *input, int *i)
{
	char	*to_print;
	int		x;

	x = 0;
	input = input + ++(*i);
	to_print = get_variable(input, &x);
	if (!to_print && !input[0])
		return ((void)write(1, "$", 1));
	if (!to_print)
		return (*i += x, (void)0);
	write(1, to_print, ft_strlen(to_print));
	*i += x;
}

static void	print_echo_input(char *input, int *i)
{
	static char	quotes;

	while (input[*i] && input[*i] != ' ')
	{
		while (input[*i] && (input[*i] == '\'' || input[*i] == '\"'))
		{
			if (!quotes)
				quotes = input[(*i)++];
			else if (input[*i] == quotes)
				quotes = ((*i)++, '\0');
			else
				break ;
		}
		if (input[*i] && input[*i] == '$' && \
		((quotes == '\"' && input[*i + 1] != '\"') || !quotes))
			print_variable(input, i);
		else if (input[*i])
			write(1, &input[(*i)++], 1);
	}
	if (quotes && !input[*i])
		quotes = '\0';
}

int	newline_opt(char *input, int *tmp)
{
	int	i;
	int quote;

	i = 0;
	quote = 0;
	if (!ft_strncmp(input + i, "-n", 2) || !ft_strncmp(input + i, "\"-n\"", 3))
	{
		*tmp = i;
		while (input[i] && input[i] != 'n')
		{
			if (input[i] == '\'' || input[i] == '\"')
				quote++;
			i++;
		}
		while (input[i] == 'n')
		{
			i++;
			while (input[i] == '\'' || input[i] == '\"')
				(quote++, i++);
		}
		if (input[i] && ((input[i] != 'n' && input[i] != ' ') \
			|| (quote % 2 != 0 && input[i] == ' ')))
			return (i = *tmp, i);
		while (input[i] && input[i] == ' ')
			i++;
	}
	return (*tmp = i, i);
}

void	echo_cmd(char *input)
{
	int	i;
	int	tmp;
	int temp;

	temp = 0;
	tmp = 0;
	input = ft_strtrim(input, " ");
	i = newline_opt(input, &tmp);
	while (i)
	{
		i += newline_opt(input + i, &temp);
		if (tmp == i)
			break;
		tmp += temp;
	}
	temp = 0;
	while (input[i])
	{
		if (input[i] == '$')
			print_variable(input, &i);
		else if (input[i] == '~' && (!input[i + 1] || input[i + 1] == '/' \
			|| input[i + 1] == ':' || input[i + 1] == ';' || input[i + 1] == ' '))
		{
			print_variable("$HOME", &temp);
			temp = 0;
			i++;
			if (input[i] == ';')
				i++;
		}
		else
			print_echo_input(input, &i);
		if (input[i] && input[i] == ' ')
			write(1, &input[i++], 1);
		while (input[i] && input[i] == ' ')
			i++;
	}
	if (!tmp)
		write(1, "\n", 1);
	free(input);
}
