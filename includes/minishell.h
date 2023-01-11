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
# include <termios.h>
# include <sys/ioctl.h>
# include <linux/kd.h>
# include <term.h>

# define FULL 0
# define SHORT 1

# define RESET 0
# define SET 1

# define EXIT 1

extern char	**environ;

/* builtins */
void	cd_cmd(char *line);
void	export_cmd(char *line, char **envp);
void	unset_cmd(char *line, char **envp);

/* terminal.c */
void	set_terminal(int option);

/* input.c */
char	*get_input(void);
int		check_exit(char *input);

/* print.c */
void	print_env(char **envp);
void	print_export(char **envp);
void	print_shell(void);
char	*get_current_path(int option);

/* signals.c */
void	signals(void);
void	exit_code(int code);

/* memory.c */
void	free_split(char **split);

/* commands.c */
int		handle_cmd(char *line, char **envp);

/* utils.c */
void	exec_cmd(char **envp, char *cmd, int fd_in, int fd_out);
int		ft_pipe(int argc, char *cmds[], char **envp, int fd[2]);

#endif
