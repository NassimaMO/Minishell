/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:02:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 13:52:59 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	main(void)
{
	char		**history;
	char		*input;
	t_cursor	curs;
	struct stat	buf;

	history = (init_env(), NULL);
	g_exit_code = 0;
	while (1)
	{
		print_shell(0);
		fstat(STDIN_FILENO, &buf);
		if (S_ISFIFO(buf.st_mode) || !isatty(STDIN_FILENO))
			input = (signals(IGNORE), get_input());
		else
			input = (signals(SET), \
			get_input_readline(ft_split_dup(history), &curs));
		if (input && *input && *input != '\n')
			history = add_split(history, input);
		if (handle_cmd(input, history) == EXIT)
			break ;
		if (input && !(*input && *input != '\n'))
			free(input);
	}
	return (free_env(), free_split(history), g_exit_code);
}
