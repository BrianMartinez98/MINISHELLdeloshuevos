/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:13:22 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 21:58:07 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPACE			"\t\n\v\f\r "

# define MAX_TOKENS 256

# define COL_MAGENTA "\033[0;35m"
# define COL_RESET "\033[0m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

# include "libs/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token //para los tokens que nos pasen
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env //para las variables de entorno
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_hist //para el historial de comandos
{
	char			*line;
	struct s_hist	*next;
	struct s_hist	*prev;
}	t_hist;

typedef struct s_span
{
	size_t			start;
	size_t			end;
}	t_span;

typedef struct s_fd
{
	int				in;
	int				out;
}	t_fd;

typedef enum e_errorlst //para los errores que pueden surgir
{
	PIPES,
	MALLOCERROR,
	FD,
	GETCWD,
	MSG,
	NCMD,
}	t_errorlst;

typedef struct s_shell //para los datos que necesitaremos en la minishell
{
	char			**env;
	t_hist			*hist;
	struct termios	termios_saved;
	char			*cwd;
	char			*prompt;
	int				exit;
	int				builtin;
	int				eof;
	int				status;
	int				last_status;
	char			*line;
	char			*line2;
	int				stdin_save;
	int				stdout_save;
	int				fd;
	int				is_child;
	size_t			len;
	ssize_t			nread;
	char			***cmds;
	int				heredoc_fd;
	int				i;
	int				n;
	int				flag;
}	t_shell;

//builtins/cd.c
int		change_path(char **tokens, t_shell *shell);

//builtins/echo.c
void	ft_echo(char **tokens, t_shell *shell);

//builtins/environment_init.c
int		ft_env_init(t_shell *shell, char **env_array);

//builtins/environment.c
void	ft_print_env(t_shell *shell);
char	*ft_getenv(t_shell *shell, const char *key);
void	ft_free_env(t_shell *shell);
int		append_env(t_shell *shell, const char *entry);

//builtins/exit.c
void	ft_exit(t_shell *shell, char **cmd);

//builtins/export_utils.c
int		is_valid_key(const char *key);
int		is_valid_value(char *equal);

//builtins/export.c
void	ft_export(char **tokens, t_shell *shell);

//builtins/history.c
void	ft_add_history(t_shell *shell);
void	ft_print_history(t_shell *shell);
void	ft_free_history(t_shell *shell);

//builtins/unset.c
void	ft_unset(char **tokens, t_shell *shell);

//srcs/execute_builtin.c
int		is_builtin(char **tokens);
int		is_echo(char **tokens);
int		ft_execute_builtin(char **tokens, t_shell *shell);

//srcs/errors.c
int		error_custom(t_shell *shell, int err_code,
			char *err_msg, char *err_key);
int		ft_error(const char *msg);
void	handle_error(t_errorlst error, t_shell *shell);

//srcs/execute_pipes.c
void	ft_execute_pipes(t_shell *shell);

//srcs/execute_utils.c
void	ft_wait_children(t_shell *shell, pid_t *pids);
void	restore_stdio(t_shell *shell);
int		error_check(int saved_stdin, int saved_stdout);
pid_t	fork_and_exec_builtin(char **tokens, t_shell *shell, t_fd fd);

//srcs/execute.c
void	close_fds_except(int keep1, int keep2, int keep3);
void	redirection_fail(t_fd fd);
pid_t	execute_command(t_shell *shell, char **tokens, int has_next, t_fd fd);

//srcs/readline.c
void	ft_readline(t_shell *shell);
void	ft_free_line(t_shell *shell);

//srcs/redirect_expand.c
char	*expand_heredoc_line(const char *line, t_shell *sh);
int		remove_quotes_and_check_expand(char **delimiter);

//srcs/redirect_helpers.c
char	*expand_heredoc_line(const char *line, t_shell *sh);

//srcs/redirect_helpers.c
char	*ft_strjoin_free(char *s1, char *s2, int free_flag);
char	*ft_strjoin_char(char *s, char c);
int		ft_redirect(t_shell *shell, char **cmd, int i);
int		ft_adding(t_shell *shell, char **cmd, int i);
int		is_redir_token(const char *t);

//srcs/redirect_heredoc.c
void	heredoc_child(t_shell *shell, int *pipefd, char *delimiter, int expand);

//srcs/redirect_utils.c
int		ft_left(t_shell *shell, char **cmd, int i);
int		ft_leftleft(t_shell *shell, char **cmd, int i);

//srcs/redirect.c
int		handle_redirections(char **cmd, t_shell *shell);
int		check_heredoc(char **cmd, t_shell *shell);
void	restore_std(t_shell *shell);

//srcs/shell_exit.c
void	ft_free_array(char ***array);
void	ft_free_matrix(char ****matrix);
int		ft_exit_shell(t_shell *shell);
void	handle_error(t_errorlst error, t_shell *shell);

//srcs/shell.c
t_shell	*ft_get_shell_address(t_shell *shell);
void	ft_disable_echoctl(t_shell *shell);
void	ft_restore_term_settings(t_shell *shell);
void	ft_init_shell(t_shell *shell, char **env);

//srcs/signals.c
void	ft_sigint_handler(int sig);
void	ft_sigquit_handler(int sig);
void	ft_setup_signals_prompt(void);
void	ft_setup_signals_child(void);

//srcs/tokens_expand.c
char	*get_env_value(t_shell *shell, const char *key);
size_t	expand_var(t_shell *shell, char **cmd, t_span span);

//srcs/tokens_parse.c
void	parse_cmds(t_shell *shell);

//src/tokens_print.c
void	print_tokens_array(t_shell *shell);

//srcs/tokens_quotes.c
int		closed_quotes(char *line, int i);
size_t	remove_quotes(char **cmd, t_span span);

//srcs/tokens_remove.c
void	remove_initial_empty_cmds(t_shell *shell);

//srcs/tokens_span.c
int		ft_next_span(char *s, size_t *i, t_span *sp);

//srcs/tokens_utils.c
int		count_pipes(t_shell *shell);
char	*copy_token(char *line, t_span sp);
void	add_token(char **cmds, int *token_idx, char *line, t_span sp);
size_t	alloc_tokens(char **cmds, char *line);

//srcs/tokens.c
void	split_line(t_shell *shell);

//src/utils_pipex.c
int		is_path_like(const char *cmd);
void	free_paths(char **paths);
char	*command_finder(char **command, char **paths);
char	**paths_finder(char **env);

//srcs/utils.c
void	ft_build_prompt(t_shell *shell);
int		ft_isspace(char c);
void	filter_args(char **args, char ***tokens, t_shell *shell);

//srcs/utils.c
char	*ft_execve_prep(char ***tkns_ptr, t_shell *shell);

#endif