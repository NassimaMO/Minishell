/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:35:42 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/12 15:09:51 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char *cmd, int fi, int fo, char **history)
{
	char	**args;
	char	*path;
	int		code;

	if (is_bin(cmd) && (built_in(cmd, fi, fo, &code), 1))
		exit((ft_close(2, fi, fo), free_env(), free(cmd), free_split(history), \
		code));
	args = process_args(get_cmd_args(cmd), 0);
	if (!args)
		exit((ft_close(2, fi, fo), free_env(), free(cmd), free_split(args), \
		free_split(history), 0));
	if (ft_strchr(args[0], '/'))
		path = relative_path(args[0]);
	else
		path = get_pathname(args[0], environ);
	dup2(fi, STDIN_FILENO);
	dup2(fo, STDOUT_FILENO);
	execve(path, args, environ);
	free_split((ft_close(2, fi, fo), history));
	if (errno == ENOENT)
		exit((print_err(args[0], SCMD), free_split(args), free_env(), \
		free(path), free(cmd), 127));
	exit((perror(""), free_split(args), free_env(), free(cmd), free(path), 1));
}

static int	*fi(int i, int fd[], int pipes[])
{
	int	*fd_in;

	if (i == 0)
	{
		if (fd[0] < 0)
		{
			fd[0] = open("/dev/null", O_RDONLY);
			if (fd[0] < 0)
				exit(EXIT_FAILURE);
		}
		fd_in = fd;
	}
	else if (i % 2)
		fd_in = pipes;
	else
		fd_in = (pipes + 2);
	return (fd_in);
}

static int	*fo(int i, int nb, int fd[], int pipes[])
{
	int	*fd_out;

	if (i == nb - 1)
	{
		fd_out = fd + 1;
		if (fd[1] < 0)
			exit(EXIT_FAILURE);
	}
	else if (i % 2)
		fd_out = pipes + 3;
	else
		fd_out = pipes + 1;
	return (fd_out);
}

void	cp(int i, int nb, int pipes[], int opt)
{
	if ((opt == IN || opt == ALL) && i != 0 && i % 2)
		close(pipes[1]);
	if ((opt == IN || opt == ALL) && i != 0 && !(i % 2))
		close((pipes + 2)[1]);
	if ((opt == OUT || opt == ALL) && i != nb - 1 && i % 2)
		close((pipes + 2)[0]);
	if ((opt == OUT || opt == ALL) && i != nb - 1 && !(i % 2))
		close(pipes[0]);
}

int	ft_pipes(int n, char **cmds, int fd[2], char **h)
{
	int		p[4];
	pid_t	pid;
	int		s;
	int		i;

	i = 0;
	while (i < n)
	{
		if (i != (n - 1) && ((!(i % 2) && pipe(p) < 0) || \
		((i % 2) && pipe(p + 2) < 0)))
			return (perror("pipe failed: "), EXIT_FAILURE);
		pid = (redirect(cmds[i], fi(i, fd, p), fo(i, n, fd, p)), fork());
		if (pid == -1)
			return (perror("fork failed: "), EXIT_FAILURE);
		if (pid == 0)
		{
			if ((cp(i, n, p, ALL), 1) && !cmds[i])
				exit((write(2, "syntax error\n", 13), free_split(cmds), 2));
			exec_cmd(ft_dupfree(cmds, i), *fi(i, fd, p), *fo(i, n, fd, p), h);
		}
		if (!i++)
			continue ;
		waitpid(pid, &s, (close((cp(i -1, n, p, IN), *(fi(i -1, fd, p)))), 0));
	}
	return (free_split(cmds), WEXITSTATUS(s));
}
