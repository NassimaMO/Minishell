/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:26:44 by nmouslim          #+#    #+#             */
/*   Updated: 2023/02/04 18:28:12 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get substring redirection file name / input delimiter from str */
static char	*delimiter(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '<')
		i++;
	if (str[i])
		i++;
	if (str[i] && str[i] == '<')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	return (ft_substr(str, i, j - i));
}

/* read stdin until delimiter and write it in a pipe */
static void	heredoc(char *delimiter, int fd_in)
{
	char	**history;
	int		pipefd[2];
	char	*tmp;

	if (pipe(pipefd) < 0)
		return ;
	history = NULL;
	ft_printf(">");
	tmp = get_input(history);
	while (tmp && (ft_strncmp(tmp, delimiter, ft_strlen(delimiter)) || \
			(ft_strlen(delimiter) != ft_strlen(tmp))))
	{
		write(pipefd[1], tmp, ft_strlen(tmp));
		write(pipefd[1], "\n", 1);
		ft_printf(">");
		free(tmp);
		tmp = get_input(history);
	}
	free(tmp);
	close(pipefd[1]);
	dup2(pipefd[0], fd_in);
	free_split(history);
}

/* changes str to remove redirection and changes fd_in */
void	redir_in(char *str, int fd_in)
{
	char	*name;
	char	*line;

	if (!ft_strchr(str, '<'))
		return ;
	name = delimiter(str);
	if (ft_strnstr(str, "<<", ft_strlen(str)))
		heredoc(name, fd_in);
	else
		dup2(open(name, O_RDONLY), fd_in);
	line = ft_strnstr(str, name, ft_strlen(str));
	while (*line && *line != ' ' && *line != '\t')
		line ++;
	ft_strlcpy(ft_strchr(str, '<'), line, ft_strlen(line) + 1);
	return (free(name));
}

/* changes str to remove redirection and changes fd_out */
void	redir_out(char *str, int fd_out)
{
	char	*name;
	int		append;
	char	*line;
	int		new_fd;

	if (!ft_strchr(str, '>'))
		return ;
	line = ft_strdup(str);
	name = ft_strchr(line, '>') + 1;
	append = 0;
	if (*name == '>' && ++name)
		append = 1;
	name = ft_strtrim(name, " \t");
	*ft_strchr(line, '>') = 0;
	line = gnl_join(line, ft_strchr(name, 32), ft_strlen(ft_strchr(name, 32)));
	if (ft_strchr(name, ' '))
		*ft_strchr(name, ' ') = 0;
	if (append)
		new_fd = open(name, O_FLAG2, S_FLAG);
	else
		new_fd = open(name, O_FLAG, S_FLAG);
	close((dup2(new_fd, fd_out), new_fd));
	return (ft_strlcpy(str, line, ft_strlen(line) + 1), free(name), free(line));
}
