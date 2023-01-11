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

void	cd_cmd(char *line)
{
	char	*str;
	char	*path;

	str = ft_strtrim(line, " ");
	if (!ft_strncmp(str, "cd", 2) && ft_strlen(str) == 2)
		chdir(getenv("HOME"));
	else if (ft_strchr(str, ' '))
	{
		path = ft_strchr(str, ' ') + 1;
		if (ft_strchr(path, '~'))
		{
			path = gnl_join(ft_strdup(getenv("HOME")), path + 1, \
													ft_strlen(path + 1));
			if (chdir(path) < 0)
				perror("");
			free(path);
		}
		else if (chdir(ft_strchr(str, ' ') + 1) < 0)
			perror("");
	}
	free(str);
}

char	*get_current_path(int option)
{
	char	*home;
	char	*path;
	char	*short_path;
	int		len;

	path = getcwd(NULL, 0);
	home = getenv("HOME");
	if (!home)
		return (path);
	if (option == SHORT && path == ft_strnstr(path, home, ft_strlen(home)))
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

void	print_env(char *envp[])
{
	int	i;

	i = 0;
	//ft_printf("\n");
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
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
	else if (ft_strchr(computer_name, '\n'))
		*ft_strchr(computer_name, '\n') = 0;
	path = get_current_path(SHORT);
	ft_printf("%s@%s:%s$ ", getenv("USER"), computer_name, path);
	free(computer_name);
	free(path);
}
