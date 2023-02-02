/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:35:42 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/25 09:35:44 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
{
	static char	*cmds[6] = {"echo", "cd", "pwd", "env", "export", "unset"};
	int			i;
	char		*s;

	i = 0;
	cmd = ft_strdup(cmd);
	s = ft_strtrim(cmd, " \t");
	free(cmd);
	while (i < 6)
	{
		if (!strncmp(s, cmds[i], ft_strlen(cmds[i])))
			return (free(s), 1);
		i++;
	}
	return (free(s), 0);
}

void	ft_error(char *s, int fd_in, int fd_out)
{
	if (errno == ENOENT)
	{
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, ": command not found\n", 20);
		ft_close(2, fd_in, fd_out);
		exit((free(s), free_env(), 127));
	}
	ft_close(2, fd_in, fd_out);
	exit((free(s), free_env(), perror(""), EXIT_FAILURE));
}

void	exec_cmd(char *cmd, int fd_i, int fd_o)
{
	char	**args;
	char	*path;
	char	*s;
	int		code;

	args = get_cmd_args(cmd);
	if (!args)
		exit((free(cmd), free_env(), 0));
	s = ft_strtrim(cmd, " \t");
	if (ft_strchr(s, ' '))
		*ft_strchr(s, ' ') = 0;
	if (ft_strchr(s, '\t'))
		*ft_strchr(s, '\t') = 0;
	dup2(fd_i, STDIN_FILENO);
	dup2(fd_o, STDOUT_FILENO);
	if (ft_strchr(s, '/'))
		path = relative_path(s);
	else
		path = get_pathname(s, environ);
	if (is_built_in(cmd) && (built_in(cmd, fd_i, fd_o, &code), 1))
		exit((ft_close(2, fd_i, fd_o), free_split(args), free(path), free(s), \
		free(cmd), free_env(), code));
	execve(path, args, environ);
	return (free_split(args), free(path), free(cmd), ft_error(s, fd_i, fd_o));
}

int	fi(int i, int fd[], int pipes[])
{
	int	fd_in;

	if (i == 0)
	{
		if (fd[0] < 0)
		{
			fd[0] = open("/dev/null", O_RDONLY);
			if (fd[0] < 0)
				exit(EXIT_FAILURE);
		}
		fd_in = fd[0];
	}
	else if (i % 2)
	{
		close(pipes[1]);
		fd_in = pipes[0];
	}
	else
	{
		close((pipes + 2)[1]);
		fd_in = (pipes + 2)[0];
	}
	return (fd_in);
}

int	fo(int i, int nb, int fd[], int pipes[])
{
	int	fd_out;

	if (i == nb - 1)
	{
		fd_out = fd[1];
		if (fd[1] < 0)
			exit(EXIT_FAILURE);
	}
	else if (i % 2)
	{
		close((pipes + 2)[0]);
		fd_out = (pipes + 2)[1];
	}
	else
	{
		close(pipes[0]);
		fd_out = pipes[1];
	}
	return (fd_out);
}

int	ft_pipes(int nb, char **cmds, int fd[2])
{
	int		p[4];
	pid_t	pid;
	int		status;
	int		i;
	char	*cmd;

	i = 0;
	while (i < nb)
	{
		if (i != (nb -1) && ((!(i % 2) && pipe(p) < 0) || \
		((i % 2) && pipe(p +2) < 0)))
			return (perror("pipe failed: "), EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (perror("fork failed: "), EXIT_FAILURE);
		if (pid == 0)
		{
			cmd = ft_strdup(cmds[i]);
			exec_cmd((free_split(cmds), cmd), fi(i, fd, p), fo(i, nb, fd, p));
		}
		if (!i++)
			continue ;
		waitpid(pid, &status, (close(fi(i - 1, fd, p)), 0));
	}
	return (free_split(cmds), WEXITSTATUS(status));
}
