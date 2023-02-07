/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:35:42 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/07 15:09:10 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char *cmd, int fd_i, int fd_o, char **h)
{
	char	**args;
	char	*path;
	int		code;

	args = process_args(get_cmd_args(cmd), 0);
	if (!args)
		exit((ft_close(2, fd_i, fd_o), free_env(), free_split(h), \
		free(cmd), free_split(args), 0));
	dup2(fd_i, STDIN_FILENO);
	dup2(fd_o, STDOUT_FILENO);
	if (is_built_in(cmd) && (built_in(cmd, fd_i, fd_o, &code), 1))
		exit((ft_close(2, fd_i, fd_o), free_split(args), free_env(), \
									free_split(h), free(cmd), code));
	if (ft_strchr(args[0], '/'))
		path = relative_path(args[0]);
	else
		path = get_pathname(args[0], environ);
	execve(path, args, environ);
	ft_close(2, fd_i, fd_o);
	free_split(h);
	if (errno == ENOENT)
		exit((print_err(args[0], SCMD), free_split(args), free_env(), \
		free(path), free(cmd), 127));
	exit((perror(""), free_split(args), free_env(), free(cmd), free(path), 1));
}

static int	fi(int i, int fd[], int pipes[])
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

static int	fo(int i, int nb, int fd[], int pipes[])
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

char	*ft_dupfree(char **cmds, int i)
{
	char	*tmp;

	tmp = ft_strdup(cmds[i]);
	free_split(cmds);
	return (tmp);
}

int	ft_pipes(int n, char **cmds, int fd[2], char **h)
{
	int		p[4];
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	while (i < n)
	{
		if (i != (n - 1) && ((!(i % 2) && pipe(p) < 0) || \
		((i % 2) && pipe(p + 2) < 0)))
			return (perror("pipe failed: "), EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (perror("fork failed: "), EXIT_FAILURE);
		if (pid == 0)
		{
			if (!cmds[i])
				exit((write(2, "syntax error\n", 13), free_split(cmds), 2));
			exec_cmd(ft_dupfree(cmds, i), fi(i, fd, p), fo(i, n, fd, p), h);
		}
		if (!i++)
			continue ;
		waitpid(pid, &status, (close(fi(i - 1, fd, p)), 0));
	}
	return (free_split(cmds), WEXITSTATUS(status));
}
