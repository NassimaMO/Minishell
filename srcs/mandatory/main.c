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

static void	init_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		environ[i] = ft_strdup(environ[i]);
		i++;
	}
}

void	ft_close(int nb, ...)
{
	va_list	args;
	int		i;
	int		fd;

	va_start(args, nb);
	i = 0;
	while (i < nb)
	{
		fd = va_arg(args, int);
		if (fd > 2)
			close(fd);
		i++;
	}
}

/* TO DO LIST :
- proper history
- file redirection : <<
- built_in variable "$?" (last exit code) */

int	main(void)
{
	char	**history;
	int		exit_code;
	char	*input;

	history = NULL;
	exit_code = 0;
	signals();
	init_env();
	while (1)
	{
		print_shell();
		input = get_input(ft_split_dup(history));
		if (handle_cmd(input, &exit_code, history) == EXIT)
			break ;
		if (input)
			history = add_split(history, input);
	}
	free_env();
	free_split(history);
	return (exit_code);
}
