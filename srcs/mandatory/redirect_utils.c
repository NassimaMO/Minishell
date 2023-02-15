/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:19:13 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/15 14:53:37 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get substring redirection file name / input delimiter from str */
static char	*delimiter(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i])
		i++;
	if (str[i] && str[i] == c)
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	return (ft_substr(str, i, j - i));
}

/* changes str to remove redirection */
static void	ft_change_str(char *str, char *name, char c)
{
	char	*line;
	int		len;
	char	*s;

	line = ft_strdup(str);
	*ft_strchr(line, c) = 0;
	s = ft_strnstr(ft_strchr(str, c), name, ft_strlen(ft_strchr(str, c)));
	if (ft_strchr(s, ' '))
	{
		len = ft_strlen(ft_strchr(s, ' '));
		line = gnl_join(line, ft_strchr(s, ' '), len);
	}
	else if (ft_strchr(s, '\t'))
	{
		len = ft_strlen(ft_strchr(s, ' '));
		line = gnl_join(line, ft_strchr(s, ' '), len);
	}
	ft_strlcpy(str, line, ft_strlen(line) + 1);
	free(line);
}

/* changes str to remove redirection and changes fd_out */
int	redir_out(char *str, int *fd_out)
{
	char	*name;
	int		new_fd;
	int		n;
	char	*s;

	name = delimiter(str, '>');
	new_fd = 0;
	if (!*name || *name == '<' || *name == '>')
		return (write(2, STXN, 13), free(name), ft_bzero(str, 1), 2);
	if (ft_strnstr(str, ">>", ft_strlen(str)))
		new_fd = open(name, O_FLAG2, S_FLAG);
	else
		new_fd = open(name, O_FLAG, S_FLAG);
	s = ft_strdup(str);
	*ft_strchr(s, '>') = '\0';
	if (ft_isdigit(*s) && !ft_atoi_err(s, &n, sizeof(int)))
		*fd_out = ((n & MSK) << 20) | ((new_fd & MSK) << 10) | (*fd_out & MSK);
	else if (new_fd > 2)
		*fd_out = (ft_close(1, *fd_out), new_fd);
	ft_strlcpy(str, ft_strchr(str, '>'), ft_strlen(ft_strchr(str, '>')) + 1);
	ft_change_str(str, name, '>');
	if (new_fd < 0)
		return (perror(name), free(name), free(s), 2);
	return (free(name), free(s), 0);
}

/* read stdin until delimiter and write it in a pipe */
static void	heredoc(char *delimiter, int *fd_in)
{
	char		**history;
	int			pipefd[2];
	t_cursor	curs;
	char		*tmp;

	if (pipe(pipefd) < 0)
		return ;
	history = NULL;
	ft_printf(">");
	tmp = get_input(history, &curs);
	while (tmp && (ft_strncmp(tmp, delimiter, ft_strlen(delimiter)) || \
			(ft_strlen(delimiter) != ft_strlen(tmp))))
	{
		write(pipefd[1], tmp, ft_strlen(tmp));
		write(pipefd[1], "\n", 1);
		ft_printf(">");
		free(tmp);
		tmp = get_input(history, &curs);
	}
	free(tmp);
	close(pipefd[1]);
	*fd_in = (ft_close(1, *fd_in), pipefd[0]);
	free_split(history);
}

/* changes str to remove redirection and changes fd_in */
int	redir_in(char *str, int *fd_in)
{
	char	*name;
	int		new_fd;

	name = delimiter(str, '<');
	new_fd = 0;
	if (!*name || *name == '<' || *name == '>')
		return (write(2, STXN, 13), free(name), ft_bzero(str, 1), 2);
	if (ft_strnstr(str, "<<", ft_strlen(str)))
		heredoc(name, fd_in);
	else
		new_fd = open(name, O_RDONLY);
	ft_change_str(str, name, '<');
	if (new_fd > 2)
		*fd_in = (ft_close(1, *fd_in), new_fd);
	else if (new_fd < 0)
		return (perror(name), free(name), 2);
	return (free(name), 0);
}
