/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:23 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/26 13:40:44 by nmouslim         ###   ########.fr       */
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
	static char	p;

	while (input[*i] && input[*i] != ' ')
	{
		while (input[*i] && (input[*i] == '\'' || input[*i] == '\"'))
		{
			if (!p)
				p = input[(*i)++];
			else if (input[*i] == p)
				p = ((*i)++, '\0');
			else
				break ;
		}
		if (input[*i] && input[*i] == '$' && \
		((p == '\"' && input[*i + 1] != '\"') || !p))
			print_variable(input, i);
		else if (input[*i])
			write(1, &input[(*i)++], 1);
	}
	if (p && !input[*i])
		p = '\0';
}

int	skip_newline(char *input, int *tmp)
{
	int	i;

	i = 0;
	while (!ft_strncmp(input + i, "-n", 2) || !ft_strncmp(input + i, "\"-n\"", 2))
	{
		*tmp = i;
		if (!ft_strncmp(input + i, "-n", 2))
			i += 2;
		else
			i += 4;
		while (input[i] && input[i] == 'n')
			i++;
		if (input[i] && input[i] != 'n' && input[i] != ' ')
		{
			i = *tmp;
			break ;
		}
			while (input[i] && input[i] == ' ')
				i++;
	}
	*tmp = i;
	return (i);
}

void	echo_cmd(char *input)
{
	int	i;
	int	tmp;
	int temp;

	temp = 0;
	tmp = 0;
	input = ft_strtrim(input, " ");
	i = skip_newline(input, &tmp);
	while (input[i])
	{
		if (input[i] == '$')
			print_variable(input, &i);
		else if (input[i] == '~' && !ft_isalpha(input[i + 1]))
			(print_variable("$HOME", &temp), temp = 0, i++);
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
