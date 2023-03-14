/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:04:22 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 13:50:47 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(void)
{
	int		i;
	int		n;
	char	*str;
	char	*line;

	i = 0;
	while (environ[i])
	{
		environ[i] = ft_strdup(environ[i]);
		if (!environ[i])
			exit((free_env(), 1));
		i++;
	}
	if (getenv("SHLVL") && !ft_atoi_err(getenv("SHLVL"), &n, sizeof(int)))
	{
		str = ft_itoa(n + 1);
		if (str)
			line = ft_strjoin("SHLVL=", str);
		if (!str || !line)
			return (add_var("SHLVL", "SHLVL=1"));
		return (add_var("SHLVL", line), free(str), free(line));
	}
	else
		add_var("SHLVL", "SHLVL=1");
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
}

int	valid_var_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if ((!ft_isalnum(name[i]) && name[i] != '_') || name[i] == ' ' \
			|| (ft_isdigit(name[i]) && i == 0))
			return (0);
		i++;
	}
	return (1);
}

void	add_var(char *name, char *line)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], tmp, ft_strlen(tmp)))
			break ;
		i++;
	}
	if (!environ[i])
		environ[i + 1] = NULL;
	if (ft_strnstr(line, "+=", ft_strlen(line)))
	{
		if (environ[i])
			tmp = gnl_join(tmp, ft_strchr(environ[i], '=') + 1, -1);
		line = ft_strjoin(tmp, ft_strchr(line, '=') + 1);
		environ[i] = (free(environ[i]), line);
	}
	else if (ft_strchr(line, '='))
		environ[i] = (free(environ[i]), ft_strdup(line));
	return (free(tmp));
}

void	del_var(char *name)
{
	int	j;

	j = 0;
	name = ft_strjoin(name, "=");
	while (environ[j])
	{
		if (!ft_strncmp(environ[j], name, ft_strlen(name)))
		{
			free(environ[j]);
			while (environ[++j])
				environ[j - 1] = environ[j];
			environ[j - 1] = NULL;
		}
		else
			j++;
	}
	free(name);
}
