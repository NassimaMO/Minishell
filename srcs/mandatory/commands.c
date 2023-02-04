/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:39:27 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/04 18:21:24 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_pipes(char *input)
{
	static char	**split = NULL;
	char		**final;
	int			i;
	char		c;

	i = 0;
	while (input[i] && input[i] != '|')
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			c = input[i++];
			while (input[i] && input[i] != c)
				i++;
		}
		if (input[i])
			i++;
	}
	if (input[i] == '|')
	{
		split = add_split(split, ft_substr(input, 0, i));
		return (split_pipes(input + i + 1));
	}
	final = add_split(split, ft_strdup(input));
	return (ft_bzero(&split, sizeof(char **)), final);
}

int	is_built_in(char *cmd)
{
	static char	*cmds[] = {"echo", "cd", "pwd", "env", "export", "unset", "exit"};
	int			i;
	char		*s;

	i = 0;
	cmd = ft_strdup(cmd);
	s = ft_strtrim(cmd, " \t");
	free(cmd);
	while (i < 7)
	{
		if (!strncmp(s, cmds[i], ft_strlen(cmds[i])))
			return (free(s), 1);
		i++;
	}
	return (free(s), 0);
}

void	built_in(char *input, int fd_in, int fd_out, int *exit_code)
{
	char	*line;
	int		std[2];

	line = ft_strtrim(input, " \t");
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	dup2(fd_out, (dup2(fd_in, 0), 1));
	if (!ft_strncmp(line, "echo", 4))
		*exit_code = echo_cmd(line + 4, *exit_code);
	else if (!ft_strncmp(line, "pwd", 3))
		*exit_code = pwd_cmd(line);
	else if (!ft_strncmp(line, "cd", 2))
		*exit_code = cd_cmd(line);
	else if (!ft_strncmp(line, "env", 3))
		*exit_code = env_cmd(line);
	else if (!ft_strncmp(line, "export", 6))
		*exit_code = export_cmd(line);
	else if (!ft_strncmp(line, "unset", 5))
		*exit_code = unset_cmd(line);
	dup2(std[1], (dup2(std[0], 0), 1));
	close(std[0]);
	close(std[1]);
	return (free(line));
}

int	handle_cmd(char *input, int *exit_code, char **history)
{
	char	**split;
	int		i;
	int		fd[2];

	if (!input)
		return (check_exit(input, exit_code));
	redirect_stdout((redirect_stdin(input, fd), input), fd);
	split = (ft_bzero(&i, sizeof(int)), split_pipes(input));
	while (split && split[i])
		i++;
	if (i > 1)
		*exit_code = ft_pipes(i, split, fd, history);
	else if (check_exit(input, exit_code) == EXIT)
		return (free_split(split), EXIT);
	if (i == 1 && !is_built_in(input) && (free_split(split), 1))
	{
		i = fork();
		if (i == 0)
			exec_cmd(input, fd[0], fd[1], history);
		waitpid(i, exit_code, 0);
		*exit_code = WEXITSTATUS(*exit_code);
	}
	else if (i <= 1 && (split && (free_split(split), 1)))
		built_in(input, fd[0], fd[1], exit_code);
	return (ft_close(2, fd[0], fd[1]), 0);
}
