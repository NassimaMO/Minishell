/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:02:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/03 17:18:56 by nmouslim         ###   ########.fr       */
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

char	**ft_split_dup(char **split)
{
	char	**to_return;
	int		i;

	to_return = malloc(sizeof(char *) * split_len(split));
	i = -1;
	while (split[++i])
		to_return[i] = ft_strdup(split[i]);
	to_return[i] = NULL;
	return (to_return);
}

int	main(void)
{
	char	**history;
	int		exit_code;
	char	*input;

	history = NULL;
	exit_code = 0;
	signals();
	set_terminal(SET);
	init_env();
	while (1)
	{
		print_shell();
		input = get_input(history);
		if (handle_cmd(input, &exit_code, ft_split_dup(history)) == EXIT)
			break ;
		if (input)
			history = add_split(history, input);
	}
	free_env();
	free_split(history);
	set_terminal(RESET);
	return (exit_code);
}
