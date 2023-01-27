/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:40 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/09 15:37:39 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

void	print_export(char **envp)
{
	int			i;
	char		*tmp;
	static char	*last = NULL;

	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		if ((i == 0 && !last) || \
		((!tmp || ft_strncmp(envp[i], tmp, ft_strlen(tmp)) < 0) && \
		(!last || ft_strncmp(envp[i], last, ft_strlen(last)) > 0)))
			tmp = envp[i];
		i++;
	}
	last = tmp;
	if (last)
	{
		if (ft_strncmp(last, "_=", 2))
			ft_printf("%s\n", last);
		print_export(envp);
	}
}

void	print_shell(void)
{
	char		*name;
	char		*path;
	int			fd[2];
	pid_t		pid;

	ft_bzero(fd, sizeof(int) * 2);
	if (pipe(fd) < 0)
		return (perror(""), ft_close(2, fd[0], fd[1]));
	pid = fork();
	if (pid < 0)
		return (perror(""), ft_close(2, fd[0], fd[1]));
	if (pid == 0)
		exit((exec_cmd("hostname", STDIN_FILENO, fd[1], environ), 0));
	name = get_next_line(fd[0]);
	wait(NULL);
	if (ft_strchr(name, '.'))
		*ft_strchr(name, '.') = '\0';
	else if (ft_strchr(name, '\n'))
		*ft_strchr(name, '\n') = '\0';
	path = get_current_path(SHORT);
	ft_printf("%s@%s:%s$ ", getenv("USER"), name, path);
	ft_close(2, fd[0], fd[1]);
	return (free(name), free(path));
}
