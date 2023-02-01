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

int	cd_cmd(char *line)
{
	char	*path;
	char	**split;
	int		i;
	char	*old;

	split = ft_split_set(line, " \t");
	i = 0;
	while (split[i])
		i++;
	if (i == 1)
		path = ft_strdup(getenv("HOME"));
	else if (i > 2)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	else if (!ft_strncmp(split[1], "-", 1) && ft_strlen(split[1]) == 1)
		path = (ft_printf("%s\n", getenv("OLDPWD")), \
				ft_strdup(getenv("OLDPWD")));
	else if (split[1][0] == '~')
		path = ft_strjoin(getenv("HOME"), split[1] + 1);
	else
		path = ft_strdup(split[1]);
	old = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	add_var("OLDPWD", old);
	if ((free_split(split), chdir(path)) < 0)
		return (perror(""), free(path), free(old), EXIT_FAILURE);
	return (free(path), free(old), 0);
}

/* option=SHORT: path with ~ ; option=0: full path */
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

int	pwd_cmd(char *input)
{
	char	*path;

	input = ft_strtrim(input, " \t");
	if (ft_strlen(input) == 3)
		path = get_current_path(FULL);
	else
	{
		ft_printf("pwd: %s\n", S2ARG);
		return (free(input), EXIT_FAILURE);
	}
	ft_printf("%s\n", path);
	return (free(input), free(path), 0);
}
