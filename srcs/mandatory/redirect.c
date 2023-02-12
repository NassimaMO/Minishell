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

/* read stdin until delimiter and write it in a pipe */
static void	heredoc(char *delimiter, int *fd_in)
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
	*fd_in = (ft_close(1, *fd_in), pipefd[0]);
	free_split(history);
}

/* changes str to remove redirection and changes fd_in */
int	redir_in(char *str, int *fd_in)
{
	char	*name;
	char	*line;

	name = delimiter(str, '<');
	if (!*name || *name == '<' || *name == '>')
		return (write(2, STXN, 13), free(name), ft_bzero(str, 1), 2);
	if (ft_strnstr(str, "<<", ft_strlen(str)))
		heredoc(name, fd_in);
	else
		*fd_in = (ft_close(1, *fd_in), open(name, O_RDONLY));
	line = ft_strnstr(str, name, ft_strlen(str));
	while (*line && *line != ' ' && *line != '\t')
		line ++;
	ft_strlcpy(ft_strchr(str, '<'), line, ft_strlen(line) + 1);
	return (free(name), 0);
}

/* changes str to remove redirection and changes fd_out */
int	redir_out(char *str, int *fd_out)
{
	char	*name;
	char	*line;
	int		len;

	name = delimiter(str, '>');
	if (!*name || *name == '<' || *name == '>')
		return (write(2, STXN, 13), free(name), ft_bzero(str, 1), 2);
	line = ft_strdup(str);
	*ft_strchr(line, '>') = 0;
	len = ft_strlen(ft_strchr(ft_strnstr(ft_strchr(str, '>'), name, \
	ft_strlen(ft_strchr(str, '>'))), 32));
	line = gnl_join(line, ft_strchr(ft_strnstr(ft_strchr(str, '>'), name, \
	ft_strlen(ft_strchr(str, '>'))), 32), len);
	if (ft_strnstr(str, ">>", ft_strlen(str)))
		*fd_out = (ft_close(1, *fd_out), open(name, O_FLAG2, S_FLAG));
	else
		*fd_out = (ft_close(1, *fd_out), open(name, O_FLAG, S_FLAG));
	free(name);
	return (ft_strlcpy(str, line, ft_strlen(line) + 1), free(line), 0);
}

int	redirect(char *str, int *fd_in, int *fd_out)
{
	int		in;
	int		out;
	int		i;
	char	c;

	ft_init(3, &i, &in, &out);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i])
				i++;
		}
		if (str[i] == '<')
			in = redir_in(str + i, fd_in);
		if (str[i] == '>')
			out = redir_out(str + i, fd_out);
		i += (str[i] != 0) + (str[i] == '>' || str[i] == '<') + ((str[i] == '>' \
		|| str[i] == '<') && (str[i + 1] == '>' || str[i + 1] == '<'));
	}
	str[0] *= (!in && !out);
	return (in + out * (in == 0));
}
