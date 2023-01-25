/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:02:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/09 18:31:21 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code(int mode, int code)
{
	static int	last = 0;

	if (mode == GET)
		return (last);
	if (mode == SET)
		last = code;
	return (last);
}

/* TO DO LIST :
- executable with relative or absolute path : may leak with SIGINT
- proper history
- built_in redirection
- file redirection : <<
- built_in variable "$?" (last exit code) */

int	main(int argc, char *argv[])
{
	int	len;

	len = env_len(environ);
	signals();
	set_terminal(SET);
	while (1)
	{
		print_shell();
		if (handle_cmd(get_input(), environ) == EXIT)
			break ;
	}
	(void)argc;
	(void)argv;
	set_terminal(RESET);
	free_env(len);
	return (exit_code(GET, 0));
}
