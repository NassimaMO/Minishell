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
//# include <term.h>

# define FULL 0
# define SHORT 1

# define RESET 0
# define SET 1
# define GET 2

# define EXIT -1

/* (O_RDWR | O_CREAT | O_TRUNC) */
# define O_FLAG 578
/* (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) */
# define S_FLAG 420

extern char	**environ;

/* path.c */
void	pwd_cmd(char *input);
void	cd_cmd(char *line);
char	*get_current_path(int option);

/* env */
void	export_cmd(char *line, char **envp);
void	unset_cmd(char *line, char **envp);
void	env_cmd(char *input, char **envp);

/* terminal.c */
void	set_terminal(int option);

/* input.c */
char	*get_input(void);
int		check_exit(char *input);

/* print.c */
void	print_env(char **envp);
void	print_export(char **envp);
void	print_shell(void);

/* signals.c */
void	signals(void);
int		exit_code(int mode, int code);

/* memory.c */
void	free_split(char **split);
void	free_env(int len);

/* commands.c */
int		built_in(char *line, char **envp);
int		handle_cmd(char *input, char **envp);
void	print_variable(char *input, int *i);

/* pipex.c */
void	exec_cmd(char *cmd, int fd_in, int fd_out, char *envp[]);
int		ft_pipes(int nb, char *cmds[], int fd[], char *envp[]);

/* utils.c */
char	*get_pathname(char *cmd, char *envp[]);
char	**get_cmd_args(const char *cmd);

#endif
