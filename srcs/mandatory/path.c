/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/25 09:36:05 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(char *line)
{
	char	*str;
	char	*path;

	str = ft_strtrim(line, " ");
	if (ft_strlen(str) == 2)
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

/* give SHORT (or 0 for full path) as option */
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

void	pwd_cmd(char *input)
{
	char	*path;

	input = ft_strtrim(input, " ");
	if (ft_strlen(input) == 3)
	{
		path = get_current_path(FULL);
		exit_code(SET, 0);
	}
	else
	{
		ft_printf("pwd: too many arguments\n");
		return (exit_code(SET, 1), free(input));
	}
	ft_printf("%s\n", path);
	return (free(input), free(path));
}
