/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:35:52 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/25 09:35:54 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_var_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
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
		environ[i] = ft_strdup(line);
	return (free(tmp));
}

int	export_cmd(char *line)
{
	char	*name;

	if (ft_strlen(line) == 6)
		return (print_export(environ), 0);
	if (!ft_strncmp(line, "export", 6))
		line = ft_strtrim(ft_strchr(line, ' '), " \t");
	if (ft_strchr(line, ' '))
		ft_bzero((export_cmd(ft_strtrim(ft_strchr(line, ' '), " \t")), \
		ft_strchr(line, ' ')), sizeof(char));
	else if (ft_strchr(line, '\t'))
		ft_bzero((export_cmd(ft_strtrim(ft_strchr(line, '\t'), " \t")), \
		ft_strchr(line, '\t')), sizeof(char));
	name = ft_strdup(line);
	if (ft_strchr(name, '='))
		*ft_strchr(name, '=') = '\0';
	else
		return (free(line), free(name), 0);
	if (ft_strchr(name, '+'))
		*ft_strchr(name, '+') = '\0';
	if (!valid_var_name(name) || !*name)
		return (ft_printf("export: not valid in this context: '%s'\n", name), \
		free(name), free(line), EXIT_FAILURE);
	return (add_var(name, line), free(name), free(line), 0);
}

int	unset_cmd(char *line)
{
	int	i;

	if (ft_strlen(line) == 5)
		return (ft_printf("unset: %s\n", SARG), EXIT_FAILURE);
	i = 0;
	if (!ft_strncmp(line, "unset", 5))
		line = ft_strtrim(ft_strchr(line, ' '), " \t");
	if (ft_strchr(line, ' '))
		ft_bzero((unset_cmd(ft_strtrim(ft_strchr(line, ' '), " \t")), \
		ft_strchr(line, ' ')), sizeof(char));
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], line, ft_strlen(line)))
		{
			free(environ[i]);
			while (environ[++i])
				environ[i - 1] = environ[i];
			environ[i - 1] = NULL;
		}
		else
			i++;
	}
	return (free(line), 0);
}

int	env_cmd(char *input)
{
	input = ft_strtrim(input, " \t");
	if (ft_strlen(input) == 3)
		return (free(input), print_env(environ), 0);
	else
		return (free(input), ft_printf("env: %s\n", S2ARG), EXIT_FAILURE);
	return (free(input), 0);
}
