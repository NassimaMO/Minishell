/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:51:04 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/02 16:03:05 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_escape(size_t *cursor, size_t *moves, char **str, char **history)
{
	char	buff[1];

	if (read(0, ft_memset(buff, 0, 1), 1) == 1 && *buff == '[')
	{
		read(0, ft_memset(buff, 0, 1), 1);
		if ((*buff == 'C' && *cursor < ft_strlen(*str) && ++(*cursor)) || \
			(*buff == 'D' && *cursor > 0 && (--(*cursor), 1)))
		{
			ft_printf("\033[1%c", *buff);
		}
		if (history && ((*buff == 'A' && *moves < split_len(history) && \
		++(*moves)) || (*buff == 'B' && *moves > 0 && (--(*moves), 1))))
		{
			ft_printf("\33[2K\r");
			print_shell();
			if (*moves == 0)
				ft_printf("%s", *str);
			else
				ft_printf("%s", history[split_len(history) - *moves]);
		}
	}
	else
	{
		// delete
	}
}

char	*get_input(char ***history)
{
	char	*str;
	char	buff[1];
	int		bytes;
	size_t	cursor;
	size_t	history_moves;

	bytes = read(0, ft_memset(buff, 0, 1), 1);
	str = ft_strdup("");
	cursor = 0;
	history_moves = 0;
	while (str && bytes >= 0 && *buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 4) && !*str)
			return (free(str), NULL);
		if (*buff == 27)
			ft_escape(&cursor, &history_moves, &str, *history);
		else if (ft_isprint(*buff))
			str = (cursor++, ft_printf("%c", *buff), gnl_join(str, buff, 1));
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	*history = add_split(*history, ft_strdup(str));
	return (ft_printf("\n"), str);
}

char	*add_char(char *str, char c, size_t cursor)
{
	(void)str;
	(void)c;
	(void)cursor;
	return (NULL);
}

/* char	*get_input(void)
{
	char				*str;
	long unsigned int	move;
	static char			**history;
	static int			len_history;
	int					history_move;
	//char			*shell;
	char				buff[1];
	int					bytes;

	shell = print_shell();
	while (ft_strchr((str = readline(shell)), '\n'))
	{
		//if (strlen(str))
		ft_add_history(str);
		free(str);
	}
	free(shell);
	move = 0;
	history_move = 0;
	bytes = read(0, ft_memset(buff, 0, 1), 1);
	str = ft_strdup("");
	while (str && bytes >= 0 && *buff != '\n')
	{
		if ((bytes == 0 || *buff == 0 || *buff == 4) && !*str)
			return (free(str), NULL);
		if (*buff == 27)
		{
			bytes = read(0, ft_memset(buff, 0, 1), 1);
			if (*buff == 91)
			{
				bytes = read(0, ft_memset(buff, 0, 1), 1);
				if ('C' == *buff)
				{
					if (move < ft_strlen(str))
					{
						ft_printf("\033[1%c", *buff);
						move++;
					}
				}
				else if (*buff == 'D')
				{
					if (move > 0)
					{
						ft_printf("\033[1%c", *buff);
						move--;
					}
				}
				else if (*buff == 'A')
				{
					if (history && history_move < len_history)
					{
						history_move++;
						free(str);
						str = ft_strdup("");
						str = gnl_join(str, history[len_history - history_move], ft_strlen(history[len_history - history_move]));
						printf("\33[2K\r");
						if (move < ft_strlen(str))
							move = ft_strlen(str) - move;
						else
							move = move - ft_strlen(str);
						printf("{%d}\n", len_history - history_move);
						while (move)
						{
							ft_printf("\033[1C");
							move--;
						}
						ft_printf("%s", str);
					}
				}
				else if (*buff == 'B')
				{
					if (history && history_move >= 0)
					{
						history_move--;
						free(str);
						str = ft_strdup("");
						str = gnl_join(str, history[len_history - history_move], ft_strlen(history[len_history - history_move]));
						printf("\33[2K\r");
						if (move < ft_strlen(str))
							move = ft_strlen(str) - move;
						else
							move = move - ft_strlen(str);
						while (move)
						{
							ft_printf("\033[1C");
							move--;
						}
						ft_printf("%s", str);
					}
				}
			}
			*buff = 0;
		}
		else if (ft_isprint(*buff))
		{
			str = gnl_join(str, buff, 1);
			move++;
			ft_printf("%c",  *buff);
		}
		bytes = read(0, ft_memset(buff, 0, 1), 1);
	}
	if (str)
	{
		if (!history)
		{
			history = malloc(sizeof(char *) * 2);
			history[0] = ft_strdup(str);
			history[1] = NULL;
			len_history++;
		}
		else
		{
			history = add_split(history , str);
			printf("\n(%s)\n", str);
		}
		len_history++;
	}
	int i = -1;
	while (++i < len_history)
		printf("\n[%d.%s]\n", i + 1, history[i]);
	return (str);
} */

int	str_into_int(char *s, void *ptr, int size, int p)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ft_isdigit(s[i]))
	{
		n *= 10;
		n += s[i] - '0';
		i++;
	}
	if (s[i])
		return (-1);
	if (size == sizeof(char))
		*(char *)ptr = (char)(p * n);
	if (size == sizeof(int))
		*(int *)ptr = (int)(p * n);
	if (size == sizeof(long))
		*(long *)ptr = (long)(p * n);
	return (0);
}

int	ft_atoi_error(const char *s, void *n, int size)
{
	int	i;
	int	p;

	i = 0;
	p = 1;
	if (s[i] == '-' && ++i)
		p = -1;
	else if (s[i] == '+')
		i++;
	if (!ft_isdigit(s[i]))
		return (-1);
	return (str_into_int((char *)s + i, n, size, p));
}

int	check_exit(char *input, int *exit_code)
{
	char	*cmd;

	if (!input)
		return (ft_printf("\nexit\n"), EXIT);
	cmd = ft_strtrim(input, " \t");
	*exit_code = 0;
	if (!ft_strncmp(input, "exit", 4))
	{
		ft_printf("exit\n");
		if (ft_strchr(cmd, ' '))
		{
			input = ft_strtrim(ft_strchr(cmd, ' '), " \t");
			if (ft_strchr(input, ' '))
			{
				*exit_code = (free(input), free(cmd), 1);
				return (ft_printf("exit: %s\n", S2ARG), 0);
			}
			if (ft_atoi_error(input, &exit_code, sizeof(char)) < 0)
				*exit_code = (ft_printf("exit: %s: %s\n", input, SNUM), 2);
			free(input);
		}
		return (free(cmd), EXIT);
	}
	return (free(cmd), 0);
}
