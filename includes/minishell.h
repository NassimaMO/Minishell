/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:05:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/09 18:31:09 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft.h"
# include "signal.h"

# include <errno.h>
# include <sys/wait.h>

/* print.c */
void	print_shell(char *envp[]);

/* signals.c */
void	control_c(void);
char	*get_input(void);

/* memory.c */
void	free_split(char **split);

/* commands.c */
void    handle_cmd(char *line, char *envp[]);

/* utils.c */
void	exec_cmd(char *envp[], char *cmd, int fd_in, int fd_out);
int		ft_pipe(int argc, char *cmds[], char *envp[], int fd[2]);

#endif
