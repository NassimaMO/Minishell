/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:39:27 by nmouslim          #+#    #+#             */
/*   Updated: 2023/03/14 16:42:28 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_pipes(char *input)
{
	int		i;
	char	c;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '|')
		return (0);
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

	args = process_args(get_cmd_args(cmd));
	if ((!*cmd && (free_split(args), 1)) || !args)
		return (0);
	i = 0;
	s = args[0];
	while (s && i < 7)
	{
		if (!strncmp(s, cmds[i], ft_strlen(cmds[i])) && \
			ft_strlen(s) == ft_strlen(cmds[i]))
			return (free_split(args), 1);
		i++;
	}
	return (free_split(args), 0);
}

void	built_in(char *input, int fd_in, int fd_out)
{
	char	*line;

	if (redirect(input, &fd_in, &fd_out))
		return ;
	ft_dup(fd_in, fd_out);
	line = ft_strtrim(input, " \t");
	if (!line)
		return ;
	if (!ft_strncmp(line, "echo", 4))
		g_exit_code = echo_cmd(line + 4);
	else if (!ft_strncmp(line, "pwd", 3))
		g_exit_code = pwd_cmd(line);
	else if (!ft_strncmp(line, "cd", 2))
		g_exit_code = cd_cmd(line);
	else if (!ft_strncmp(line, "env", 3))
		g_exit_code = env_cmd(line);
	else if (!ft_strncmp(line, "export", 6))
		g_exit_code = export_cmd(line);
	else if (!ft_strncmp(line, "unset", 5))
		g_exit_code = unset_cmd(line);
	free(line);
}

int	handle_cmd(char *s, char **h)
{
	char		**cmd;
	int			fd[5];
	int			i;

	if ((init_fd(fd, 4), 1) && !s)
		return (check_exit(s));
	cmd = split_pipes(s);
	if (!cmd)
		return (write(2, STXN, 13 * (ft_strchr(s, '|') != NULL)), 2);
	i = split_len(cmd);
	if (i > 1)
		g_exit_code = ft_pipes(i, cmd, fd, h);
	else if (check_exit(s) == EXIT)
		return (free_split(cmd), EXIT);
	s = ft_strdup(s);
	if (i == 1 && (free_split(cmd), !redirect(s, fd, fd +1)) && !is_bin(s))
	{
		i = (signals(IGNORE), fork());
		if (i == 0)
			exec_cmd(s, fd[0], fd[1], h);
		g_exit_code = (waitpid(i, &g_exit_code, 0), WEXITSTATUS(g_exit_code));
	}
	else if (i == 1 && is_bin(s) && (set_std(fd + 2, SET), 1))
		set_std(fd + 2, (built_in(s, *fd, fd[1]), RESET));
	return (ft_close(2, fd[0], fd[1]), free(s), signals(SET), 0);
}
