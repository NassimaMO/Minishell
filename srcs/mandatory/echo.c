/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:23 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/03 16:51:20 by nmouslim         ###   ########.fr       */
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

void	print_input(char *input, int i, int tmp, int exit_code)
{
	char	*output;

	while (input[i])
	{
		output = quote_gestion(input, &i, exit_code);
		(ft_printf("%s", output), free(output));
		if (input[i] && input[i] == ' ')
			write(1, &input[i++], 1);
		while (input[i] && input[i] == ' ')
			i++;
	}
	if (!tmp || !i)
		write(1, "\n", 1);
}

int	echo_cmd(char *input, int exit_code)
{
	int		i;
	int		tmp;
	int		temp;
	
	temp = 0;
	tmp = 0;
	if (input[0] && input[0] != ' ' && input[0] != '\t')
		return (ft_printf("echo%s: command not found\n", input), 127);
	input = ft_strtrim(input, " \t");
	i = newline_opt(input, &tmp);
	while (i)
	{
		i += newline_opt(input + i, &temp);
		if (tmp == i)
			break ;
		tmp += temp;
	}
	print_input(input, i, tmp, exit_code);
	return (free(input), 0);
}
