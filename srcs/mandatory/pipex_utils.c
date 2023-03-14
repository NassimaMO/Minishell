/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:36:31 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 15:32:24 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_arg(char **split, const char *cmd, int *i)
{
	char	*str;
	char	c;
	int		j;

	str = ft_strdup(cmd + *i);
	j = *i;
	while (cmd[*i] && cmd[*i] != ' ' && cmd[*i] != '\t')
	{
		if (cmd[*i] == '\'' || cmd[*i] == '\"')
		{
			c = cmd[(*i)++];
			while (cmd[*i] && cmd[*i] != c)
				(*i)++;
		}
		if (cmd[*i])
			(*i)++;
	}
	str[*i - j] = 0;
	if (*str)
		return (add_split(split, str));
	return (free(str), split);
}

char	**get_cmd_args(const char *cmd)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		split = get_arg(split, cmd, &i);
	}
	return (split);
}

static char	**get_path(char *envp[])
{
	int		i;
	char	**split;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) == envp[i])
		{
			split = ft_split(envp[i], ':');
			if (!split)
				return (NULL);
			ft_strlcpy(split[0], split[0] + 5, ft_strlen(split[0] + 5) + 1);
			return (split);
		}
		i++;
	}
	return (NULL);
}

char	*get_pathname(char *cmd, char *envp[])
{
	char	*s1;
	char	*s2;
	char	**split;
	int		i;

	split = get_path(envp);
	i = 0;
	cmd = ft_strtrim(cmd, " \t");
	if (!cmd || !split)
		return (cmd);
	while (split[i])
	{
		s1 = ft_strjoin(split[i], "/");
		if (!s1)
			return (free(cmd), free_split(split), ft_strdup(""));
		s2 = ft_strjoin(s1, cmd);
		free(s1);
		if (s2 && access(s2, X_OK) == 0)
			return (free_split(split), free(cmd), s2);
		i++;
		if (s2)
			free(s2);
	}
	return (free_split(split), free(cmd), ft_strdup(""));
}

char	*relative_path(char *path)
{
	char	*new_path;
	char	**split;
	int		i;
	int		len;

	if (*path == '/')
		return (ft_strdup(path));
	new_path = get_current_path(0);
	if (*path == '~')
		new_path = (free(new_path), ft_strdup(getenv("HOME")));
	split = ft_split(path, '/');
	i = 0;
	while (split[i])
	{
		len = ft_strlen(split[i]);
		if (!ft_strncmp(split[i], "..", len) && len == 2)
		{
			if (ft_strrchr(new_path, '/'))
				*ft_strrchr(new_path, '/') = 0;
		}
		else if ((*(split[i]) != '.' && *(split[i]) != '~') || len > 1)
			new_path = gnl_join(gnl_join(new_path, "/", 1), split[i], len);
		i++;
	}
	return (free_split(split), new_path);
}
