/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:02:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/02 13:41:54 by nmouslim         ###   ########.fr       */
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
*/

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
		input = get_input(&history);
		if (handle_cmd(input, &exit_code, history) == EXIT)
			break ;
	}
	free_env();
	free_split(history);
	return (exit_code);
}
