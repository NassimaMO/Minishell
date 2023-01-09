/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:15:15 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/05 14:15:17 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char *envp[])
{
	int		i;
	char	**split;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) == envp[i])
		{
			split = ft_split(envp[i], ':');
			ft_strlcpy(split[0], split[0] + 5, ft_strlen(split[0] + 5) + 1);
			return (split);
		}
		i++;
	}
	return (NULL);
}

char	*get_pathname(char *cmd, char *envp[])
{
	char	*s1;
	char	*s2;
	char	**split;
	int		i;

	split = get_path(envp);
	if (!split)
		exit((write(STDERR_FILENO, "Error env\n", 10), 1));
	i = 0;
	while (split[i])
	{
		s1 = ft_strjoin(split[i], "/");
		if (!s1)
			return (NULL);
		s2 = ft_strjoin(s1, cmd);
		free(s1);
		if (s2 && access(s2, X_OK) == 0)
			return (free_split(split), s2);
		i++;
		if (s2)
			free(s2);
	}
	return (free_split(split), NULL);
}

void	exec_cmd(char *envp[], char *cmd, int fd_in, int fd_out)
{
	char		**args;
	char		*pathname;
	static int	no = 0;

	args = ft_split(cmd, ' ');
	if (!args)
		exit((write(STDERR_FILENO, "Error alloc\n", 12), 1));
	if (!*args)
		exit((free_split(args), ft_printf("%s: command not found\n", cmd), no));
	pathname = get_pathname(*args, envp);
	if (!pathname)
		exit((free_split(args), ft_printf("%s: command not found\n", cmd), no));
	if (fork() == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(pathname, args, envp);
	}
	else
		wait(NULL);
	close(fd_in);
	close(fd_out);
	return (no++, free(pathname), free_split(args));
}

int	fd_error(int fd_in, int fd_out, char *file_in, char *file_out)
{
	if (fd_in < 0)
		ft_printf("%s: %s\n", file_in, strerror(errno));
	if (fd_out < 0)
		ft_printf("%s: %s\n", file_out, strerror(errno));
	if (fd_out < 0)
		return (1);
	return (0);
}

int	ft_pipe(char *envp[], char *argv[], int argc)
{
	int	pipes[4];
	int	i;
	int	fd[2];

	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR, S_IWUSR);
	if (fd[0] < 0)
		ft_printf("%s: %s\n", fd[0], strerror(errno));
	if (fd[1] < 0)
		ft_printf("%s: %s\n", fd[1], strerror(errno));
	if (pipe(pipes) < 0)
		return (ft_printf("Error pipe\n"));
	exec_cmd(envp, argv[2], fd[0], pipes[1]);
	i = 3;
	while (i < argc - 2)
	{
		if ((i % 2 && pipe(pipes + 2) == 0) || (!(i % 2) && pipe(pipes) == 0))
			exec_cmd(envp, argv[i], pipes[2 *!(i % 2)], pipes[2 *(i % 2) + 1]);
		else
			return (ft_printf("Error pipe\n"));
		i++;
	}
	exec_cmd(envp, argv[i], pipes[2 * !(i % 2)], fd[1]);
	return (0);
}
