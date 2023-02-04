/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:23 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/04 19:25:41 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_opt(char *input, int i, int quote, int *tmp)
{
	if (input[i] && ((input[i] != 'n' && input[i] != ' ') \
			|| (quote % 2 != 0 && input[i] == ' ')))
		return (i = *tmp, i);
	while (input[i] && input[i] == ' ')
		i++;
	return (*tmp = i, i);
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
	}
	return (is_valid_opt(input, i, quote, tmp));
}

char	*get_processed_input(char *input, int opt, int exit_code)
{
	char	*output;
	int		i;

	i = 0;
	output = ft_strdup("");
	while (input[i])
	{
		i = quote_gestion(input, &output, i, exit_code);
		if (input[i] && input[i] == ' ')
			output = gnl_join(output, input + i++, 1);
		while (input[i] && input[i] == ' ')
			i++;
	}
	if (!opt)
		output = gnl_join(output, "\n", 1);
	return (output);
}

int	echo_cmd(char *input, int exit_code)
{
	int		i;
	int		tmp;
	int		temp;
	char	*to_print;

	temp = 0;
	tmp = 0;
	if (input[0] && input[0] != ' ' && input[0] != '\t')
		return (write(2, "echo", 4), write(2, input, ft_strlen(input)), \
		write(2, ": command not found\n", 20), 127);
	input = ft_strtrim(input, " \t");
	i = newline_opt(input, &tmp);
	while (i)
	{
		i += newline_opt(input + i, &temp);
		if (tmp == i)
			break ;
		tmp += temp;
	}
	to_print = get_processed_input(input + i, tmp, exit_code);
	ft_printf("%s", to_print);
	return (free(to_print), free(input), 0);
}
