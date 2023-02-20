/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:02:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/05 15:21:25 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	**history;
	char	*input;

	history = NULL;
	g_exit_code = 0;
	signals();
	init_env();
	while (1)
	{
		print_shell(0);
		input = get_input(ft_split_dup(history));
		if (input && *input && *input != '\n')
			history = add_split(history, input);
		if (handle_cmd(input, history) == EXIT)
			break ;
		if (input && !(*input && *input != '\n'))
			free(input);
	}
	free_env();
	free_split(history);
	return (g_exit_code);
}
