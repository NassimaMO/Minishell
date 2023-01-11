/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:39:27 by nmouslim          #+#    #+#             */
/*   Updated: 2023/01/09 18:28:07 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo_input(char *input, int *i, int len)
{
	static int	nl;

	(void)len;
	if (!ft_strncmp(input, "-n", 2) && *i == 1)
		nl++;
	while (input[*i] && input[*i] != ' ')
	{
		//printf("||%c||\n", input[*i]);
		write(1, &input[*i], 1);
		(*i)++;
	}
	//printf("|||||||||||||||||||||||||||||||||\n");
}

void	print_variable(char **envp, char *input, int *i)
{
	int		x;
	char	*variable;

	x = 0;
	while (input[x] != ' ')
		x++;
	variable = malloc(sizeof(char) * x + 1);
	x = 0;
	while (input[x] != ' ')
	{
		variable[x] = input[x];
		x++;
	}
	variable[x] = '\0';
	while (envp[x])
	{
		if (ft_strnstr(envp[x], variable, ft_strlen(envp[x])) == envp[x])
			return (write(1, envp[x] + ft_strlen(variable), ft_strlen(envp[x] + \
			ft_strlen(variable))), *i += ft_strlen(variable), free(variable));
		x++;
	}
	free(variable);
}

void	echo_handle_function(char **envp, char *input)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(input + i);
	while (i < len)
	{
		//printf("||%c||\n", input[i]);
		if (input[i] == '$')
			print_variable(envp, input + i, &i);
		else
			print_echo_input(input + (i - 1), &i, len);
		if (input[i] == ' ')
			write(1, &input[i++], 1);
	}
}

int	handle_cmd(char *input, char **envp)
{
	char	*line;

	if (check_exit(input) == EXIT)
		return (EXIT);
	line = ft_strtrim(input, " ");
	if (!ft_strncmp(line, "echo", 4))
		echo_handle_function(envp, line + 4);
	if (!ft_strncmp(line, "pwd", 3) && ft_strlen(line) == 3)
		ft_printf("\n%s\n", get_current_path(FULL));
	if (!ft_strncmp(line, "cd", 2))
		cd_cmd(line);
	if (!ft_strncmp(line, "env", 3) && ft_strlen(line) == 3)
		print_env(envp);
	if (!ft_strncmp(line, "export", 6))
		export_cmd(line, envp);
	if (!ft_strncmp(line, "unset", 5))
		unset_cmd(line, envp);
	free(line);
	free(input);
	return (0);
}
