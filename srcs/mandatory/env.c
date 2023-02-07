/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:35:52 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/05 15:15:09 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_var_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if ((!ft_isalnum(name[i]) && name[i] != '_') || name[i] == ' ')
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

int	export_cmd(char *str, int exit_code)
{
	char	*line;
	char	**args;
	int		i;

	args = get_cmd_args(str);
	if (split_len(args) == 1)
		return (print_export(environ), 0);
	i = (ft_bzero(&exit_code, sizeof(int)), 1);
	while (args[i])
	{
		line = get_processed_input(args[i], 1, exit_code);
		ft_strlcpy(args[i], line, ft_strlen(line) + 1);
		if (!ft_strchr(args[i], '=') && ++i)
			continue ;
		*ft_strchr(args[i], '=') = '\0';
		if (args[i][ft_strlen(args[i]) - 1] == '+')
			args[i][ft_strlen(args[i]) - 1] = '\0';
		if (!valid_var_name(args[i]) || !*args[i])
			exit_code = (write(2, "export: not a valid identifier: ", \
	32), write(2, "'", 1), ft_putstr_fd(args[i], 2), write(2, "'\n", 2), 1);
		else
			add_var(args[i], line);
		i = (free(line), i + 1);
	}
	return (free_split(args), exit_code);
}

int	unset_cmd(char *str, int exit_code)
{
	int		i;
	char	*line;

	str = get_processed_input(str, 1, exit_code);
	if (ft_strlen(str) == 5)
		return (print_err("unset", SARG), free(str), EXIT_FAILURE);
	i = 0;
	if (!ft_strncmp(str, "unset", 5))
		line = ft_strtrim(ft_strchr(str, ' '), " \t");
	if (ft_strchr(line, ' '))
		ft_bzero((unset_cmd(ft_strtrim(ft_strchr(line, ' '), " \t"), exit_code), \
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
	return (free(line), free(str), 0);
}

int	env_cmd(char *input)
{
	input = ft_strtrim(input, " \t");
	if (ft_strlen(input) == 3)
		return (free(input), print_env(environ), 0);
	else
		return (free(input), print_err("env", S2ARG), EXIT_FAILURE);
	return (free(input), 0);
}
