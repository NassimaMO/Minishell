/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:39:27 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/05 15:11:38 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_pipes(char *input)
{
	int		i;
	char	c;

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
	return (i);
}

static char	**split_pipes(char *input)
{
	static char	**split = NULL;
	char		**final;
	int			i;

	final = NULL;
	i = parse_pipes(input);
	if (input[i] == '|' && i)
	{
		split = add_split(split, ft_substr(input, 0, i));
		return (split_pipes(input + i + 1));
	}
	else if (i)
		final = add_split(split, ft_strdup(input));
	else
		final = (free_split(split), NULL);
	split = NULL;
	return (final);
}

int	is_bin(char *cmd)
{
	static char	*cmds[] = \
	{"echo", "cd", "pwd", "env", "export", "unset", "exit"};
	int			i;
	char		**args;
	char		*s;

	i = 0;
	args = process_args(get_cmd_args(cmd), 0);
	if ((!*cmd && (free_split(args), 1)) || !args)
		return (0);
	s = args[0];
	if (s && (!ft_strncmp(args[0], "<", 1) || !ft_strncmp(args[0], ">", 1)))
	{
		s = args[1];
		if (s)
			s = args[2];
	}
	while (s && i < 7)
	{
		if (!strncmp(s, cmds[i], ft_strlen(cmds[i])))
			return (free_split(args), 1);
		i++;
	}
	return (free_split(args), 0);
}

void	built_in(char *input, int fd_in, int fd_out, int *exit_code)
{
	char	*line;

	redirect(input, &fd_in, &fd_out);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	ft_close(2, fd_in, fd_out);
	line = ft_strtrim(input, " \t");
	if (!ft_strncmp(line, "echo", 4))
		*exit_code = echo_cmd(line + 4, *exit_code);
	else if (!ft_strncmp(line, "pwd", 3))
		*exit_code = pwd_cmd(line);
	else if (!ft_strncmp(line, "cd", 2))
		*exit_code = cd_cmd(line, *exit_code);
	else if (!ft_strncmp(line, "env", 3))
		*exit_code = env_cmd(line);
	else if (!ft_strncmp(line, "export", 6))
		*exit_code = export_cmd(line, *exit_code);
	else if (!ft_strncmp(line, "unset", 5))
		*exit_code = unset_cmd(line, *exit_code);
	return (free(line));
}

int	handle_cmd(char *s, int *x, char **h)
{
	char		**cmd;
	int			fd[4];
	int			i;

	if ((init_fd(fd, 4), 1) && !s)
		return (check_exit(s, x));
	cmd = split_pipes(s);
	if (!cmd)
		return (write(2, STXN, 13 * (ft_strchr(s, '|') != NULL)), 2);
	i = split_len(cmd);
	if (i > 1)
		*x = ft_pipes(i, cmd, fd, h);
	else if (check_exit(s, x) == EXIT)
		return (free_split(cmd), EXIT);
	s = ft_strdup(s);
	if (i == 1 && !is_bin(s) && (free_split(cmd), redirect(s, fd, fd +1), 1))
	{
		if (fork() == 0)
			exec_cmd(s, fd[0], fd[1], h);
		wait(x);
		*x = WEXITSTATUS(*x);
	}
	else if (i == 1 && is_bin(s) && (set_std(fd + 2, SET), 1))
		set_std(fd +2, (free_split((built_in(s, *fd, fd[1], x), cmd)), 0));
	return (ft_close(2, fd[0], fd[1]), free(s), 0);
}
