/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:40 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 16:17:45 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

void	print_export(char **envp)
{
	int			i;
	char		*tmp;
	static char	*last = NULL;

	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		if ((i == 0 && !last) || \
		((!tmp || ft_strncmp(envp[i], tmp, ft_strlen(tmp)) < 0) && \
		(!last || ft_strncmp(envp[i], last, ft_strlen(last)) > 0)))
			tmp = envp[i];
		i++;
	}
	last = tmp;
	if (last)
	{
		if (ft_strncmp(last, "_=", 2))
			ft_printf("%s\n", last);
		print_export(envp);
	}
}

char	*get_cmd(char *cmd)
{
	int		fd[2];
	int		stdclone;
	char	*name;
	pid_t	pid;

	ft_bzero(fd, sizeof(int) * 2);
	if (pipe(fd) < 0)
		return (perror(""), NULL);
	stdclone = dup(STDERR_FILENO);
	close(STDERR_FILENO);
	pid = fork();
	if (pid < 0)
		return (perror(""), close(stdclone), close(fd[0]), close(fd[1]), NULL);
	name = ft_strdup(cmd);
	if (pid == 0)
		exec_cmd(name, 0, (close(stdclone), close(fd[0]), fd[1]), 0);
	waitpid((close(fd[1]), pid), NULL, 0);
	name = (free(name), get_next_line(fd[0]));
	ft_close(2, (dup2(stdclone, STDERR_FILENO), stdclone), fd[0]);
	if (ft_strchr(name, '.'))
		*ft_strchr(name, '.') = '\0';
	else if (ft_strchr(name, '\n'))
		*ft_strchr(name, '\n') = '\0';
	return (name);
}

size_t	print_shell(int opt)
{
	char			*name;
	char			*user;
	char			*path;
	static size_t	len;

	if (opt == LEN)
		return (len);
	set_terminal(SET);
	name = get_cmd("/bin/hostname");
	user = get_cmd("/bin/id -u -n");
	path = get_current_path(SHORT);
	if (len != ft_strlen(user) + ft_strlen(name) + ft_strlen(path) + 4)
		len = ft_strlen(user) + ft_strlen(name) + ft_strlen(path) + 4;
	ft_printf("%s@%s:%s$ ", user, name, path);
	set_terminal(RESET);
	return (free(name), free(path), free(user), len);
}

void	print_err(const char *cmd, const char *error)
{
	write(2, cmd, gnl_strlen(cmd));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
