/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:35:52 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 14:08:19 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_cmd(char *str)
{
	char	*line;
	char	**args;
	int		i;

	args = process_args(get_cmd_args(str));
	if (split_len(args) <= 1)
		return (free_split(args), print_export(environ), 0);
	i = (ft_bzero(&g_exit_code, sizeof(int)), 1);
	while (args[i])
	{
		line = ft_strdup(args[i]);
		ft_strlcpy(args[i], line, ft_strlen(line) + 1);
		if (!ft_strchr(args[i], '=') && (free(line), ++i))
			continue ;
		*ft_strchr(args[i], '=') = '\0';
		if (*(args[i]) && args[i][ft_strlen(args[i]) - 1] == '+')
			args[i][ft_strlen(args[i]) - 1] = '\0';
		if (!valid_var_name(args[i]) || !*args[i])
			g_exit_code = (write(2, "export: not a valid identifier: ", \
	32), write(2, "'", 1), ft_putstr_fd(args[i], 2), write(2, "'\n", 2), 1);
		else
			add_var(args[i], line);
		i = (free(line), i + 1);
	}
	return (free_split(args), g_exit_code);
}

int	unset_cmd(char *str)
{
	char	**args;
	int		i;

	args = process_args(get_cmd_args(str));
	if (!split_len(args))
		return (free_split(args), 0);
	i = 1;
	while (args[i])
	{
		del_var(args[i]);
		i++;
	}
	return (free_split(args), 0);
}

int	env_cmd(char *input)
{
	input = ft_strtrim(input, " \t");
	if (!input)
		return (0);
	if (ft_strlen(input) == 3)
		return (free(input), print_env(environ), 0);
	return (free(input), print_err("env", S2ARG), 1);
}
