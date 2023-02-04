/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:05:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/02/04 18:15:46 by nmouslim         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>

# define FULL 0
# define SHORT 1

# define RESET 0
# define SET 1

# define EXIT 1

# define SARG "not enough arguments"
# define S2ARG "too many arguments"
# define SNUM "numeric argument required"

/* (O_RDWR | O_CREAT | O_TRUNC) */
# define O_FLAG 578
/* (O_RDWR | O_CREAT | O_APPEND) */
# define O_FLAG2 1090
/* (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) */
# define S_FLAG 420

extern char	**environ;

/* redirect.c */
void	redirect_stdin(char *str, int fd[2]);
void	redirect_stdout(char *str, int fd[2]);

/* ft_split_set.c */
char	**ft_split_set(char *str, char *charset);

/* echo.c */
int		echo_cmd(char *input, int *exit_code);

/* quotes.c */
int		quote_gestion(char *input, char **output, int i, int *exit_code);

/* path.c */
int		pwd_cmd(char *input);
int		cd_cmd(char *line);
char	*get_current_path(int option);

/* env */
void	add_var(char *name, char *line);
int		export_cmd(char *line);
int		unset_cmd(char *line);
int		env_cmd(char *input);

/* terminal.c */
void	set_terminal(int option);

/* input.c */
char	*get_input(char **history);
int		check_exit(char *input, int *exit_code);

/* print.c */
void	print_env(char **envp);
void	print_export(char **envp);
void	print_shell(void);

/* signals.c */
void	signals(void);

/* split.c */
char	**add_split(char **split, char *str);
void	free_split(char **split);
size_t	split_len(char **split);
void	free_env(void);

/* commands.c */
void	ft_close(int nb, ...);
void	built_in(char *input, int fd_in, int fd_out, int *exit_code);
int		handle_cmd(char *input, int *exit_code, char **history);

/* pipex.c */
int		is_built_in(char *cmd);
void	exec_cmd(char *cmd, int fd_i, int fd_o, char **h);
int		ft_pipes(int n, char **cmds, int fd[2], char **h);

/* pipex_utils.c */
char	*get_pathname(char *cmd, char *envp[]);
char	**get_cmd_args(const char *cmd);
char	*relative_path(char *path);

#endif
