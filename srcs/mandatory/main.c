/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:02:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/02 13:40:38 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		environ[i] = ft_strdup(environ[i]);
		i++;
	}
}

/* TO DO LIST :
- executable with relative or absolute path : may leak with SIGINT
- proper history
- file redirection : <<
- built_in variable "$?" (last exit code) */

int	main(void)
{
	char	**history;
	int		exit_code;

	history = NULL;
	exit_code = 0;
	signals();
	set_terminal(SET);
	init_env();
	while (1)
	{
		print_shell();
		if (handle_cmd(get_input(&history), &exit_code) == EXIT)
			break ;
	}
<<<<<<< HEAD
	(void)argc;
	(void)argv;
	//free_split(history);
=======
	free_env();
	free_split(history);
>>>>>>> b5ff8cd995b3e64d0460b64220fd001474562bed
	set_terminal(RESET);
	return (exit_code);
}
