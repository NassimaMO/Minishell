/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:40 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/09 15:32:51 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_path(void)
{
	char	*home;
	char	*path;
	char	*short_path;
	int		len;

	path = getcwd(NULL, 0);
	home = getenv("HOME");
	if (home && path == ft_strnstr(path, home, ft_strlen(home)))
	{
		len = ft_strlen(path) - ft_strlen(home);
		short_path = malloc(len + 2);
		short_path[0] = '~';
		ft_strlcpy(short_path + 1, path + ft_strlen(home), len + 1);
		free(path);
		return (short_path);
	}
	return (path);
}

void	print_shell(char *envp[])
{
	char		*computer_name;
	char		*path;
	int			fd[2];
	static char	*cmds[3] = {"echo", "hostname", NULL};
	static char	**env = NULL;

	if (!env && envp)
		env = envp;
	else if (!env)
		return ;
	if (pipe(fd) < 0)
		return ;
	ft_pipe(2, cmds, env, fd);
	computer_name = get_next_line(fd[0]);
	if (ft_strchr(computer_name, '.'))
		*ft_strchr(computer_name, '.') = 0;
	path = get_current_path();
	ft_printf("%s@%s:%s$ ", getenv("USER"), computer_name, path);
	free(computer_name);
	free(path);
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
