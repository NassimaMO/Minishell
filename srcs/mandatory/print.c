/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:22:40 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/31 08:42:14 by nmouslim         ###   ########.fr       */
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

char	*get_name(char *cmd)
{
	int		fd[2];
	int		stdclone;
	char	*name;
	pid_t	pid;

	ft_bzero(fd, sizeof(int) * 2);
	if (pipe(fd) < 0)
		return (perror(""), ft_close(2, fd[0], fd[1]), NULL);
	stdclone = dup(STDERR_FILENO);
	close(STDERR_FILENO);
	pid = fork();
	if (pid < 0)
		return (perror(""), ft_close(2, fd[0], fd[1]), NULL);
	name = ft_strdup(cmd);
	if (pid == 0)
		exec_cmd(name, STDIN_FILENO, (close(stdclone), close(fd[0]), fd[1]), 0);
	wait(NULL);
	name = (free(name), get_next_line(fd[0]));
	close((dup2(stdclone, STDERR_FILENO), stdclone));
	if (ft_strchr(name, '.'))
		*ft_strchr(name, '.') = '\0';
	else if (ft_strchr(name, '\n'))
		*ft_strchr(name, '\n') = '\0';
	return (ft_close(2, fd[0], fd[1]), name);
}

void	print_shell(void)
{
	char	*name;
	char	*user;
	char	*path;

	name = get_name("/bin/hostname");
	user = get_name("/bin/id -u -n");
	path = get_current_path(SHORT);
	ft_printf("%s@%s:%s$ ", user, name, path);
	return (free(name), free(path), free(user));
}
