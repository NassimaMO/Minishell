/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:23 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/31 10:52:15 by nmouslim         ###   ########.fr       */
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

/*void	variables(char *input, int *i)
{
	
}*/

char	*quote_gestion(char *input, int *i)
{
	static char	quotes;
	int			x;
	char		*variable_tmp;
	char		*to_return;

	to_return = ft_strdup("");
	x = 0;
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
		{
			variable_tmp = ((*i)++, get_variable(input + *i, &x));
			if (!variable_tmp && (!input[*i] || input[*i] == ' '))
				to_return = gnl_join(to_return, "$", 1);
			else if (variable_tmp)
				to_return = gnl_join(to_return, variable_tmp, \
					ft_strlen(variable_tmp));
			*i += x;
			x = 0;
		}
		else if (input[*i] && input[*i] == '~' && (!input[*i + 1] \
			|| input[*i + 1] == '/' || input[*i + 1] == ':' \
			|| input[*i + 1] == ';' || input[*i + 1] == ' '))
		{
			variable_tmp = get_variable("HOME", &x);
			if (variable_tmp)
				to_return = gnl_join(to_return, variable_tmp, \
					ft_strlen(variable_tmp));
			(*i)++;
			x = 0;
			if (input[*i] && input[*i] == ';')
				i++;
		}
		else if (input[*i])
			to_return = gnl_join(to_return, input + (*i)++, 1);
	}
	if (quotes && !input[*i])
		quotes = '\0';
	return (to_return);
}

int	newline_opt(char *input, int *tmp)
{
	int	i;
	int	quote;

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
			{
				quote++;
				i++;
			}
		}
		if (input[i] && ((input[i] != 'n' && input[i] != ' ') \
			|| (quote % 2 != 0 && input[i] == ' ')))
			return (i = *tmp, i);
		while (input[i] && input[i] == ' ')
			i++;
	}
	return (*tmp = i, i);
}

int	echo_cmd(char *input)
{
	char	*output;
	int		i;
	int		tmp;
	int		temp;

	temp = 0;
	tmp = 0;
	write(1, "\n", 1);
	if (input[0] && input[0] != ' ' && input[0] != '\t')
		return (ft_printf("echo %s: command not found\n", input), 1);
	input = ft_strtrim(input, " \t");
	i = newline_opt(input, &tmp);
	while (i)
	{
		i += newline_opt(input + i, &temp);
		if (tmp == i)
			break ;
		tmp += temp;
	}
	while (input[i])
	{
		output = quote_gestion(input, &i);
		(ft_printf("%s", output), free(output));
		if (input[i] && input[i] == ' ')
			write(1, &input[i++], 1);
		while (input[i] && input[i] == ' ')
			i++;
	}
	if (!tmp || !i)
		write(1, "\n", 1);
	return (free(input), 0);
}
