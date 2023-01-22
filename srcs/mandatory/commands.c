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

void	print_echo_input(char *input, int *i)
{
	static char	p;

	while (input[*i] && input[*i] != ' ')
	{
		while (input[*i] == '\'' || input[*i] == '\"')
		{
			if (!p)
				p = input[(*i)++];
			else if (input[*i] == p)
			{
				p = '\0';
				(*i)++;
			}
			else
				break ;
		}
		printf("(p=%c, i=%d)\n", p, *i);
		if (input[*i] == '$' && p == '\"')
		{
			(*i)++;
			print_variable(input, i);
			continue ;
		}
		write(1, &input[*i], 1);
		(*i)++;
	}
	if (!input[*i])
		p = '\0';
}

void	print_variable(char *input, int *i)
{
	int		x;
	char	*variable;
	char	*to_print;

	if (input[*i] == '\'' || input[*i] == '\"')
		return (print_echo_input(input, i));
	input = input + (*i);
	x = 0;
	while (input[x] && input[x] != ' ' && input[x] != '\'' && input[x] != '\"')
		x++;
	variable = malloc(sizeof(char) * x + 1);
	x = 0;
	while (input[x] && input[x] != ' ' && input[x] != '\'' && input[x] != '\"')
	{
		variable[x] = input[x];
		x++;
	}
	variable[x] = '\0';
	to_print = getenv(variable);
	if (to_print)
	{
		write(1, to_print, ft_strlen(to_print));
		*i += ft_strlen(variable);
	}
	else
		*i += ft_strlen(variable);
	free(variable);
}

void	echo_handle_function(char *input)
{
	int	i;
	int	len;

	i = 0;
	input = ft_strtrim(input, " ");
	if (input[0] && input[1] && input[0] == '-' && input[1] == 'n')
	{
		i += 2;
		while (input[i] && input[i] == ' ')
			i++;
	}
	len = ft_strlen(input);
	while (i < len)
	{
		if (input[i] == '$')
			print_variable(input, (++i, &i));
		else
			print_echo_input(input, &i);
		if (input[i] == ' ')
			write(1, &input[i++], 1);
	}
	if (i && ft_strncmp(input, "-n", 2))
		write(1, "\n", 1);
}

void	redirect(char *line, int fd[2])
{
	char	*s;
	char	c;

	fd[0] = 0;
	fd[1] = 1;
	c = 0;
	if (ft_strchr(line, '<'))
		c = '<';
	else if (ft_strchr(line, '>'))
		c = '>';
	if (!c)
		return ;
	s = ft_strtrim(ft_strchr(line, c) + 1, " ");
	if (ft_strchr(s, ' ') && c == '<')
		ft_strlcpy(line, ft_strchr(s, ' '), ft_strlen(ft_strchr(s, ' ')) + 1);
	if (ft_strchr(s, ' '))
		*ft_strchr(s, ' ') = 0;
	if (c == '<')
		fd[0] = open(s, O_RDONLY);
	if (c == '>')
		fd[1] = (ft_bzero(ft_strrchr(line, '>'), 1), open(s, O_FLAG, S_FLAG));
	free(s);
	if (ft_strchr(line, '>'))
		redirect(line, fd);
}

int	handle_cmd(char *input, char **envp)
{
	char	**split;
	int		i;
	int		fd[2];
	int		status;

	if (!input)
		return (check_exit(input));
	redirect(input, fd);
	split = ft_split(input, '|');
	i = 0;
	while (split && split[i])
		i++;
	if (i > 1)
		status = ft_pipes(i, split, fd, envp);
	else if (check_exit(input) == EXIT)
		return (free_split(split), free(input), EXIT);
	else if (!built_in(input, envp))
	{
		i = fork();
		if (i == 0)
			exec_cmd(input, fd[0], fd[1], envp);
		waitpid(i, &status, 0);
	}
	return (free_split(split), free(input), WEXITSTATUS(status));
}

int	built_in(char *input, char **envp)
{
	char	*line;

	line = ft_strtrim(input, " ");
	if (!ft_strncmp(line, "echo", 4))
		return (echo_handle_function(line + 4), free(line), 1);
	if (!ft_strncmp(line, "pwd", 3))
		return (pwd_cmd(line), free(line), 1);
	if (!ft_strncmp(line, "cd", 2))
		return (cd_cmd(line), free(line), 1);
	if (!ft_strncmp(line, "env", 3))
		return (env_cmd(line, envp), free(line), 1);
	if (!ft_strncmp(line, "export", 6))
		return (export_cmd(line, envp), free(line), 1);
	if (!ft_strncmp(line, "unset", 5))
		return (unset_cmd(line, envp), free(line), 1);
	return (free(line), 0);
}
