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
		while (input[*i] && (input[*i] == '\'' || input[*i] == '\"'))
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
		if (input[*i] && input[*i] == '$' && (p == '\"' || !p) && input[*i + 1] != '\"') //problem: "$"VARIABLE
		{
			print_variable(input, i);
			continue ;
		}
		write(1, &input[*i], 1);
		(*i)++;
	}
	if (p && !input[*i])
		p = '\0';
}

void	print_variable(char *input, int *i)
{
	int		x;
	char	*variable;
	char	*to_print;

	(*i)++;
	if (input[*i] && (input[*i] == '\'' || input[*i] == '\"'))
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
	free(variable);
	if (!to_print)
		return (*i += x, (void)0);
	write(1, to_print, ft_strlen(to_print));
	*i += x;
}

void	echo_handle_function(char *input)
{
	int	i;

	i = 0;
	input = ft_strtrim(input, " ");
	if (input[0] && input[1] && input[0] == '-' && input[1] == 'n')
	{
		i += 2;
		while (input[i] && input[i] == ' ')
			i++;
	}
	while (input[i])
	{
		if (input[i] == '$')
			print_variable(input, &i);
		else
			print_echo_input(input, &i);
		while (input[i] == ' ')
			write(1, &input[i++], 1);
	}
	if (i && ft_strncmp(input, "-n", 2))
		write(1, "\n", 1);
	free(input);
}

/* change str to remove redirection and change fd[0] */
void	redirect_stdin(char *str, int fd[2])
{
	char	*name;
	char	*line;

	fd[0] = 0;
	if (!ft_strchr(str, '<'))
		return ;
	line = ft_strdup(str);
	name = ft_strtrim(ft_strchr(line, '<') + 1, " ");
	*ft_strchr(line, '<') = 0;
	line = gnl_join(line, ft_strchr(name, 32), ft_strlen(ft_strchr(name, 32)));
	if (ft_strchr(name, ' '))
		*ft_strchr(name, ' ') = 0;
	fd[0] = open(name, O_RDONLY);
	ft_strlcpy(str, line, ft_strlen(line) + 1);
	return (free(name), free(line));
}

/* change str to remove redirection and change fd[1] */
void	redirect_stdout(char *str, int fd[2])
{
	char	*name;
	int		append;
	char	*line;

	fd[1] = 1;
	if (!ft_strchr(str, '>'))
		return ;
	line = ft_strdup(str);
	name = ft_strchr(line, '>') + 1;
	append = 0;
	if (name[0] == '>')
	{
		append = 1;
		name ++;
	}
	name = ft_strtrim(name, " ");
	*ft_strchr(line, '>') = 0;
	line = gnl_join(line, ft_strchr(name, 32), ft_strlen(ft_strchr(name, 32)));
	if (ft_strchr(name, ' '))
		*ft_strchr(name, ' ') = 0;
	if (append)
		fd[1] = open(name, O_FLAG2, S_FLAG);
	else
		fd[1] = open(name, O_FLAG, S_FLAG);
	return (ft_strlcpy(str, line, ft_strlen(line) + 1), free(name), free(line));
}

int	handle_cmd(char *input, char **envp)
{
	char	**split;
	int		i;
	int		fd[2];
	int		status;

	if (!input)
		return (check_exit(input));
	redirect_stdin(input, fd);
	redirect_stdout(input, fd);
	split = ft_split(input, '|');
	i = 0;
	while (split && split[i])
		i++;
	if (i > 1)
		status = ft_pipes(i, split, fd, envp);
	else if (check_exit(input) == EXIT)
		return (free_split(split), free(input), EXIT);
	else if (!built_in(input, fd, envp))
	{
		i = fork();
		if (i == 0)
			exec_cmd(input, fd[0], fd[1], envp);
		waitpid(i, &status, 0);
	}
	return (free_split(split), free(input), WEXITSTATUS(status));
}

int	built_in(char *input, int fd[2], char **envp)
{
	char	*line;
	int		std[2];
	int		b;

	b = 1;
	line = ft_strtrim(input, " ");
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	dup2(fd[1], (dup2(fd[0], 0), 1));
	if (!ft_strncmp(line, "echo", 4))
		echo_handle_function(line + 4);
	else if (!ft_strncmp(line, "pwd", 3))
		pwd_cmd(line);
	else if (!ft_strncmp(line, "cd", 2))
		cd_cmd(line);
	else if (!ft_strncmp(line, "env", 3))
		env_cmd(line, envp);
	else if (!ft_strncmp(line, "export", 6))
		export_cmd(line, envp);
	else if (!ft_strncmp(line, "unset", 5))
		unset_cmd(line, envp);
	else
		b = 0;
	dup2(std[1], (dup2(std[0], 0), 1));
	return (free(line), close(std[0]), close(std[1]), b);
}
