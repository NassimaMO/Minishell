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

int	update_path(char *path, int print)
{
	char	*pwd;
	char	*var;

	pwd = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		write(2, "cd: ", 5);
		perror(path);
		return (free(path), free(pwd), EXIT_FAILURE);
	}
	var = ft_strjoin("OLDPWD=", pwd);
	add_var("OLDPWD", var);
	free(pwd);
	free(var);
	pwd = getcwd(NULL, 0);
	var = ft_strjoin("PWD=", pwd);
	add_var("PWD", var);
	free(pwd);
	free(var);
	if (print)
		ft_printf("%s\n", path);
	return (free(path), 0);
}

char	*get_home()
{
	char	*home;
	char	*cmd;
	char	*user;
	char	**split;

	home = getenv("HOME");
	if (home)
		return (ft_strdup(home));
	cmd = "getent passwd ";
	user = get_cmd("/bin/id -u -n");
	cmd = ft_strjoin(cmd, user);
	free(user);
	home = get_cmd(cmd);
	split = ft_split(home, ':');
	if (split && split_len(split) > 5)
		home = (free(home), ft_strdup(split[5]));
	else
		home = NULL;
	return (free(cmd), free_split(split), home);
}

int	cd_cmd(char *line)
{
	char	*path;
	char	**split;
	int		print;

	split = ft_split_set(line, " \t");
	print = 0;
	if (split_len(split) == 1)
		path = get_home();
	else if (split_len(split) > 2)
		return (write(2, "cd: too many arguments\n", 23), free_split(split), 1);
	else if (!ft_strncmp(split[1], "-", 1) && ft_strlen(split[1]) == 1)
	{
		if (!getenv("OLDPWD"))
			return (write(2, "cd: OLDPWD not set\n", 19), free_split(split), 1);
		path = ft_strdup(getenv("OLDPWD"));
		print = 1;
	}
	else if (split[1][0] == '~')
		path = gnl_join(get_home(), split[1] + 1, ft_strlen(split[1] + 1));
	else
		path = ft_strdup(split[1]);
	return (free_split(split), update_path(path, print));
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
		write(2, "pwd: ", 5);
		write(2, S2ARG, ft_strlen(S2ARG));
		write(2, "\n", 1);
		return (free(input), EXIT_FAILURE);
	}
	ft_printf("%s\n", path);
	return (free(input), free(path), 0);
}
