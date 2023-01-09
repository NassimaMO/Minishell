/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:40 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/09 15:22:41 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shell(void)
{
	char	*user_name;
	char	*computer_name;
	char	*path;

	user_name = getenv("USER");
	if (!user_name)
		user_name = "";
	computer_name = "";
	path = "";
	ft_putstr_fd(user_name, STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(computer_name, STDOUT_FILENO);
	ft_putchar_fd(':', STDOUT_FILENO);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putchar_fd('$', STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
}

char	*get_input(void)
{
	char	*line;

	line = get_next_line(0);
	if (line && !ft_strncmp(line, "exit\n", 5))
	{
		printf("exit\n");
		free(line);
		exit(0);
	}
	if (!line)
	{
		printf("\nexit\n");
		exit(0);
	}
	return (line);
}