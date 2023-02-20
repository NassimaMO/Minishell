/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:23:10 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/14 15:17:24 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote_closed(char quote, char *input, int i)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
		return (0);
	return (1);
}

static void	ft_quotes(char *quotes, char *input, int *i)
{
	while (input[*i] && (input[*i] == '\'' || input[*i] == '\"'))
	{
		if (!(*quotes) && is_quote_closed(input[*i], input, *i))
			*quotes = input[(*i)++];
		else if (input[*i] == *quotes)
			*quotes = ((*i)++, '\0');
		else
			break ;
	}
}

void	quote_gestion(char *input, char **output)
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
			code = ft_itoa(g_exit_code);
			*output = gnl_join(*output, code, ft_strlen(code));
			free((i += 2, code));
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
		quote_gestion(input + i, output);
}
