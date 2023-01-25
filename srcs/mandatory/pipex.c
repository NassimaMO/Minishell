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

void	exec_cmd(char *cmd, int fd_in, int fd_out, char *envp[])
{
	char	**args;
	char	*path;
	char	*s;

	args = get_cmd_args(cmd);
	s = ft_strtrim(cmd, " ");
	if (ft_strchr(s, ' '))
		*ft_strchr(s, ' ') = 0;
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	path = get_pathname(s, envp);
	execve(path, args, envp);
	write(STDERR_FILENO, "minishell: line 1: ", 19);
	if (errno == ENOENT)
	{
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit((free_split(args), free(path), free(s), free(cmd), 127));
	}
	else
		exit((free_split(args), free(s), free(path), free(cmd), perror(""), 1));
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

int	ft_pipes(int nb, char *cmds[], int fd[], char *envp[])
{
	int		pipes[4];
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	while (i < nb)
	{
		if (i != (nb -1) && ((!(i % 2) && pipe(pipes) < 0) || \
		((i % 2) && pipe(pipes +2) < 0)))
			return (perror("pipe failed: "), EXIT_FAILURE);
		if (built_in(cmds[i], fd, envp) && ++i)
			continue ;
		pid = fork();
		if (pid == -1)
			return (perror("fork failed: "), EXIT_FAILURE);
		if (pid == 0)
			exec_cmd(cmds[i], fi(i, fd, pipes), fo(i, nb, fd, pipes), envp);
		if (!i++)
			continue ;
		close(fi(i - 1, fd, pipes));
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}
