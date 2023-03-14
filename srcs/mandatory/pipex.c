/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:35:42 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 16:09:51 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char *cmd, int fi, int fo, char **history)
{
	char	**args;
	char	*path;

	if (is_bin(cmd) && (built_in(cmd, fi, fo), 1))
		exit((ft_close(2, fi, fo), free_env(), free(cmd), free_split(history), \
		g_exit_code));
	args = process_args(get_cmd_args(cmd));
	if (!args || !*args || ! **args)
		exit((ft_close(2, fi, fo), free_env(), free(cmd), free_split(args), \
		free_split(history), 0));
	if (ft_strchr(args[0], '/'))
		path = relative_path(args[0]);
	else
		path = get_pathname(args[0], environ);
	signals((ft_dup(fi, fo), RESET));
	execve(path, args, environ);
	free_split(history);
	if (errno == ENOENT)
		exit((print_err(args[0], SCMD), free_split(args), free_env(), \
		free(path), free(cmd), 127));
	exit((perror(""), free_split(args), free_env(), free(cmd), free(path), 1));
}

static int	*fi(int i, int fd[2], int *pipes)
{
	int	*fd_in;

	if (i == 0)
	{
		if (fd[0] < 0)
			fd[0] = open("/dev/null", O_RDONLY);
		fd_in = fd;
	}
	else
		fd_in = pipes;
	return (fd_in);
}

static int	*fo(int i, int n, int fd[2], int *pipes)
{
	int	*fd_out;

	if (i == n - 1)
		fd_out = fd + 1;
	else
		fd_out = pipes + 1;
	return (fd_out);
}

int	wait_pids(pid_t *pids, int n, int fd[2], int *pipes)
{
	int	i;
	int	status;
	int	fd_i;

	i = 0;
	status = 1;
	while (i < n - 1)
	{
		fd_i = *fi(i, fd, pipes);
		waitpid(pids[i], NULL, 0);
		ft_close(2, fd_i, *fo(i, n, fd, pipes));
		i++;
	}
	if (pids[i])
		status = (WEXITSTATUS(waitpid(pids[i], &status, 0)), status);
	free(pids);
	signals(SET);
	return (status);
}

int	ft_pipes(int n, char **cmds, int fd[2], char **hist)
{
	pid_t	*pids;
	int		pipes[2];
	int		i;
	int		fd_i;

	i = (signals(IGNORE), 0);
	pids = ft_calloc(n, sizeof(pid_t));
	while (i < n)
	{
		fd_i = *fi(i, fd, pipes);
		if (i != n - 1 && pipe(pipes) < 0)
			return (perror(""), free_split(cmds), free(pids), signals(SET), 1);
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror(""), ft_close(3, fd_i, pipes[0], pipes[1]), \
					free_split(cmds), free(pids), signals(SET), 1);
		if (pids[i] == 0 && (close(pipes[i == n - 1]), (!redirect(cmds[i], \
			&fd_i, fo(i, n, fd, pipes)) || i != n - 1) && (free(pids), 1)))
			exec_cmd(ft_dupfree(cmds, i), fd_i, *fo(i, n, fd, pipes), hist);
		ft_close(2, fd_i, *fo(i, n, fd, pipes));
		i++;
	}
	return (free_split(cmds), wait_pids(pids, n, fd, pipes));
}
