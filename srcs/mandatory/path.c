/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/05 15:22:30 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_path(char *path, char *arg)
{
	char	*pwd;
	char	*var;

	if (chdir(path) < 0)
	{
		write(2, "cd: ", 5);
		perror(path);
		return (free(path), EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(path), EXIT_FAILURE);
	var = ft_strjoin("OLDPWD=", pwd);
	add_var("OLDPWD", var);
	free(pwd);
	free(var);
	pwd = getcwd(NULL, 0);
	var = ft_strjoin("PWD=", pwd);
	add_var("PWD", var);
	free(pwd);
	free(var);
	if (arg && !ft_strncmp(arg, "-", 1) && ft_strlen(arg) == 1)
		ft_printf("%s\n", path);
	return (free(path), 0);
}

static char	*get_home(void)
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

int	cd_cmd(char *str)
{
	char	*path;
	char	**args;

	args = process_args(get_cmd_args(str));
	str = ft_strtrim(str + 2, " \t");
	if (!getenv("HOME") && (*str == '~' || split_len(args) == 1))
	{
		if (split_len(args) == 1)
			return (print_err("cd", SCDH), free_split(args), free(str), 1);
		path = gnl_join(get_home(), str + 1, ft_strlen(str + 1));
	}
	else if (split_len(args) == 1)
		path = get_home();
	else if (split_len(args) > 2)
		return (print_err("cd", S2ARG), free_split(args), free(str), 1);
	else if (!ft_strncmp(args[1], "-", 1) && ft_strlen(args[1]) == 1)
	{
		if (!getenv("OLDPWD"))
			return (print_err("cd", SCDO), free_split(args), free(str), 1);
		path = ft_strdup(getenv("OLDPWD"));
	}
	else
		path = ft_strdup(args[1]);
	g_exit_code = update_path(path, args[1]);
	return (free_split(args), free(str), g_exit_code);
}

/* option=SHORT: path with ~ ; option=0: full path */
char	*get_current_path(int option)
{
	char	*home;
	char	*path;
	char	*short_path;
	int		len;

	path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup(getenv("PWD"));
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
		print_err("pwd", S2ARG);
		return (free(input), EXIT_FAILURE);
	}
	ft_printf("%s\n", path);
	return (free(input), free(path), 0);
}
