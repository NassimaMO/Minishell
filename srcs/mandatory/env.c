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

void	add_var(char *name, char *line, char **envp)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], tmp, ft_strlen(tmp)))
			return (ft_strlcpy(envp[i], line, ft_strlen(line) + 1), free(tmp));
		i++;
	}
	envp[i] = ft_strdup(line);
	ft_strlcpy(envp[i], line, ft_strlen(line) + 1);
	envp[i + 1] = NULL;
	free(tmp);
}

/* need error text when '=' alone */
void	export_cmd(char *line, char **envp)
{
	char	*name;

	if (ft_strlen(line) == 6)
		return (print_export(envp));
	if (!ft_strncmp(line, "export", 6))
		line = ft_strtrim(ft_strchr(line, ' '), " ");
	if (ft_strchr(line, ' '))
	{
		export_cmd(ft_strtrim(ft_strchr(line, ' '), " "), envp);
		*ft_strchr(line, ' ') = '\0';
	}
	name = ft_strdup(line);
	if (ft_strchr(name, '='))
		*ft_strchr(name, '=') = '\0';
	else
		line = (free(line), gnl_join(ft_strdup(name), "=''", 3));
	if (!valid_var_name(name))
	{
		ft_printf("export: not valid in this context: %s\n", name);
		return (free(name), free(line));
	}
	add_var(name, line, envp);
	free(name);
	free(line);
}

void	unset_cmd(char *line, char **envp)
{
	int	i;

	if (ft_strlen(line) == 5)
		return ((void)ft_printf("unset: not enough arguments\n"));
	i = 0;
	if (!ft_strncmp(line, "unset", 5))
		line = ft_strtrim(ft_strchr(line, ' '), " ");
	if (ft_strchr(line, ' '))
	{
		unset_cmd(ft_strtrim(ft_strchr(line, ' '), " "), envp);
		*ft_strchr(line, ' ') = '\0';
	}
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], line, ft_strlen(line)))
		{
			free(envp[i]);
			while (envp[++i])
				envp[i - 1] = envp[i];
			envp[i - 1] = NULL;
		}
		else
			i++;
	}
	free(line);
}

void	env_cmd(char *input, char **envp)
{
	input = ft_strtrim(input, " ");
	if (ft_strlen(input) == 3)
	{
		print_env(envp);
		exit_code(SET, 0);
	}
	else
	{
		ft_printf("env: too many arguments\n");
		exit_code(SET, 1);
	}
	return (free(input));
}
