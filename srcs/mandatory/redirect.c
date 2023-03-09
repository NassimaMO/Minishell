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

void	ft_close(int nb, ...)
{
	va_list		args;
	int			i;
	int			fd;
	struct stat	buf;
	int			err;

	err = (va_start(args, nb), errno);
	i = 0;
	while (i < nb)
	{
		fd = va_arg(args, int);
		if ((fd >> 20) & MSK)
		{
			ft_close(1, (fd >> 20) & MSK);
			if ((fd >> 10) & MSK)
				ft_close(1, (fd >> 10) & MSK);
			ft_close(1, fd & MSK);
		}
		else if ((fd & MSK) > 2 && fstat(fd, &buf) == 0)
			close(fd);
		i++;
	}
	errno = err;
}

void	ft_dup(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	ft_close(1, fd_in);
	dup2(fd_out & MSK, STDOUT_FILENO);
	ft_close(1, fd_out & MSK);
	if (((fd_out >> 20) & MSK) && ((fd_out >> 10) & MSK))
	{
		dup2((fd_out >> 10) & MSK, (fd_out >> 20) & MSK);
		ft_close(1, (fd_out >> 10) & MSK);
	}
}

static void	ft_skip_quotes(char *str, int *i)
{
	char	c;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		c = str[(*i)++];
		while (str[*i] && str[*i] != c)
			(*i)++;
		if (str[*i])
			(*i)++;
	}
}

int	redirect(char *str, int *fd_in, int *fd_out)
{
	int		in;
	int		out;
	int		i;

	ft_init(3, &i, &in, &out);
	while (str[i])
	{
		ft_skip_quotes(str, &i);
		if (str[i] == '<')
			in = redir_in(str + i, fd_in);
		else if (str[i] == '>')
		{
			while (i != 0 && ft_isdigit(str[i - 1]))
				i--;
			out = redir_out(str + i, fd_out);
		}
		else
			i += (str[i] != 0);
		if (in || out)
			g_exit_code = (ft_bzero(str, ft_strlen(str)), in + out * (in == 0));
	}
	return (in + out * (in == 0));
}
