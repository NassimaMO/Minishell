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

	x = 0;
	while (input[*x] && input[*x] != ' ' && input[*x] != '\'' && input[*x] != '\"')
		(*x)++;
	variable = malloc(sizeof(char) * (*x + 1));
	x = 0;
	while (input[*x] && input[*x] != ' ' && input[*x] != '\'' && input[*x] != '\"')
	{
		variable[*x] = input[*x];
		(*x)++;
	}
	variable[*x] = '\0';
	to_return = getenv(variable);
	free(variable);
	if (to_return)
		return (NULL);
	return (to_return);
}

static void	print_variable(char *input, int *i)
{
	char	*to_print;
	int		x;

	input = input + ++(*i);
	to_print = get_variable(input, &x);
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
		{
			print_variable(input, i);
			continue ;
		}
		write(1, &input[(*i)++], 1);
	}
	if (input[*i] == ' ')
		write(1, &input[(*i)++], 1);
	if (p && !input[*i])
		p = '\0';
}

void	echo_cmd(char *input)
{
	int	i;

	i = 0;
	input = ft_strtrim(input, " ");
	if (!ft_strncmp(input, "-n", 2))
	{
		i += 2;
		while (input[i] && input[i] == ' ')
			i++;
	}
	while (input[i])
	{
		if (input[i] == '$')
			print_variable(input, &i);
		else
			print_echo_input(input, &i);
		while (input[i] == ' ')
			i++;
	}
	if (ft_strncmp(input, "-n", 2))
		write(1, "\n", 1);
	free(input);
}
