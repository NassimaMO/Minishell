/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:05:38 by nghulam-          #+#    #+#             */
/*   Updated: 2023/03/14 14:41:48 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft.h"

# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# define LEFT 'D'
# define RIGHT 'C'

# define LEN 1

# define ALL 0
# define IN 1
# define OUT 2

# define FULL 0
# define SHORT 1

# define RESET 0
# define SET 1
# define HEREDOC 2
# define IGNORE 3

# define EXIT 1

# define SARG "not enough arguments"
# define S2ARG "too many arguments"
# define SNUM "numeric argument required"
# define SCMD "command not found"
# define SCDH "HOME not set"
# define SCDO "OLDPWD not set"
# define SHDOC "here-document delimited by end-of-file"
# define STXN "syntax error\n"

/* (O_RDWR | O_CREAT | O_TRUNC) */
# define O_FLAG 578
/* (O_RDWR | O_CREAT | O_APPEND) */
# define O_FLAG2 1090
/* (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) */
# define S_FLAG 420

# define MSK 1023

extern char	**environ;
extern int	g_exit_code;
/* int			g_exit_code;
 */
typedef struct s_cursor {
	size_t	cursor;
	int		x;
	int		y;
}	t_cursor;

/* signals.c */
void	signals(int option);

/* print.c */
char	*get_cmd(char *cmd);
void	print_env(char **envp);
void	print_export(char **envp);
size_t	print_shell(int opt);
void	print_err(const char *cmd, const char *error);

/* init.c */
void	ft_init(int nb, ...);
void	init_fd(int *fd, size_t size);
void	set_terminal(int option);
void	set_std(int std[3], int opt);
void	set_ctrl_keys(int option);

/* input_utils.c */
void	get_cursor_pos(int *x, int *y);
void	go_through_input(char *input, char **to_return, int *i, char quotes);

/* input.c */
char	*get_input_readline(char **history, t_cursor *curs);
char	*get_input(void);

/* manage_input.c */
void	ft_move(t_cursor *curs, char direction, int n);
void	process_input(char **history, char *buff, size_t *moves, \
					t_cursor *curs);

/* history.c */
void	ft_escape(t_cursor *curs, size_t *moves, char **history);
void	change_curs(t_cursor *curs, char direction, int n);

/* split.c */
char	**ft_split_dup(char **split);
char	**add_split(char **split, char *str);
void	free_split(char **split);
size_t	split_len(char **split);
char	*ft_dupfree(char **split, int i);

/* commands.c */
int		is_bin(char *cmd);
void	built_in(char *input, int fd_in, int fd_out);
int		handle_cmd(char *input, char **history);

/* quotes.c */
void	quote_gestion(char *input, char **output);

/* pipex.c */
void	exec_cmd(char *cmd, int fi, int fo, char **history);
int		ft_pipes(int n, char **cmds, int fd[2], char **h);

/* pipex_utils.c */
char	*get_pathname(char *cmd, char *envp[]);
char	**get_cmd_args(const char *cmd);
char	*relative_path(char *path);

/* redirect_utils.c */
int		redir_out(char *str, int *fd_out);
int		redir_in(char *str, int *fd_in);

/* redirect.c */
void	ft_close(int nb, ...);
void	ft_dup(int fd_in, int fd_out);
int		redirect(char *str, int *fd_in, int *fd_out);

/* echo.c */
char	*get_processed_input(char *input, int opt);
char	**process_args(char **args);
int		echo_cmd(char *input);

/* path.c */
int		pwd_cmd(char *input);
int		cd_cmd(char *line);
char	*get_current_path(int option);

/* env */
int		export_cmd(char *str);
int		unset_cmd(char *line);
int		env_cmd(char *input);

/* env_utils.c */
void	add_var(char *name, char *line);
void	init_env(void);
void	free_env(void);
int		valid_var_name(char *name);
void	del_var(char *name);

/* exit.c */
int		ft_atoi_err(const char *s, void *n, size_t size);
int		check_exit(char *input);

#endif
