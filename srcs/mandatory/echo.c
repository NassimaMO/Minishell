/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:23 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/12 13:32:05 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_opt(char *input, int i, int quote, int *tmp)
{
	if (input[i] && ((input[i] != 'n' && input[i] != ' ') \
			|| (quote % 2 != 0 && input[i] == ' ')))
		return (i = *tmp, i);
	while (input[i] && input[i] == ' ')
		i++;
	return (*tmp = i, i);
}

static int	newline_opt(char *input, int *tmp)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (!ft_strncmp(input, "-n", 2) || !ft_strncmp(input, "\"-n", 3))
	{
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
		return (is_valid_opt(input, i, quote, tmp));
	}
	return (0);
}

char	*get_processed_input(char *input, int opt)
{
	char	*output;

	output = ft_strdup("");
	quote_gestion(input, &output);
	if (!opt)
		output = gnl_join(output, "\n", 1);
	return (output);
}

char	**process_args(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!args)
		return (NULL);
	while (args[i])
	{
		tmp = get_processed_input(args[i], 1);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
	return (args);
}

int	echo_cmd(char *input)
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
		temp = 0;
		i += newline_opt(input + i, &temp);
		if (tmp == i)
			break ;
		tmp += temp;
	}
	to_print = get_processed_input(input + i, tmp);
	ft_printf("%s", to_print);
	return (free(to_print), free(input), 0);
}
