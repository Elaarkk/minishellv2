/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:32:33 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 16:28:38 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h> 
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

# define HEREDOC 0
# define APPEND 1
# define INPUT 2
# define OUTPUT 3
# define PIPE 4
# define NORMAL 5
# define CMD 6
# define ARG 7

extern pid_t	g_signal_pid;

typedef struct s_prompt
{
	char			*text;
	int				token;
	bool			is_error;
	bool			expand;
	struct s_prompt	*next;
	struct s_prompt	*prev;
}				t_prompt;

typedef struct s_cmd
{
	pid_t			child;
	int				is_dir;
	char			*cmd_name;
	char			*cmd_arg_line;
	char			*cmd_path;
	char			**arg;
	bool			infile;
	int				infile_fd;
	bool			outfile;
	int				outfile_fd;
	bool			append;
	int				append_fd;
	bool			heredoc_expand;
	int				status_code;
	int				cmd_nb;
	int				error;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_minishell
{
	t_prompt	*prompt;
	t_cmd		*cmd;
	char		**env;
	char		**path;
	int			exit_code;
}				t_minishell;

void		ft_putstr_fd(char *s, int fd);

int			check_dir(char	*path);

void		*ft_memset(void *s, int c, size_t n);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_strcmp(char *s1, char *s2);

char		*token_operand(int token);

char		*token_normal(char *content, int *len);

t_prompt	*create_prompt(char *content, int token, t_prompt **first);

void		ft_lstadd_back(t_prompt **lst, t_prompt *new);

t_prompt	*cut_prompt(char *content);

size_t		ft_strlen(const char *s);

int			skip_spaces(char *content);

void		print_error(char *s);

void		exit_clean(int code, t_prompt **prompt);

int			analyse_prompt(t_minishell *minishell);

void		free_all(t_prompt **lst);

int			parse_prompt(t_prompt **prompt);

int			check_quotes(char *prompt);

char		*ft_strdup(const char *s);

size_t		ft_strlcpy(char *dst, const char *src, size_t siz);

size_t		ft_strlcat(char *dst, const char *src, size_t size);

t_cmd		*create_cmd_node(void);

void		add_cmd(t_prompt *prompt, t_cmd **cmd,
				int *i, t_minishell *minishell);

void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);

void		cmd_operand(t_prompt *prompt, t_cmd **cmd,
				int *i, t_minishell *minishell);

char		**cmd_normal(t_prompt *prompt, t_cmd **cmd,
				int *i, t_minishell *minishell);

void		free_split(int i, char **split);

void		free_all_cmd(t_cmd **lst);

void		free_all_prompt(t_prompt **lst);

void		exec_init(t_minishell *minishell, char **path);

char		*ft_strnstr(const char *big, const char *little, size_t len);

char		**ft_split(char const *s, char c);

char		*ft_strjoin(char *s1, char *s2);

char		*ft_strchr(const char *s, int c);

void		exec_cmd(t_minishell *minishell);

char		*ft_getenv(char **env, char *loc);

int			ft_cd(t_cmd *cmd, char **env);

int			close_two_fd(int fd1, int fd2);

int			first_child(t_cmd *cmd, char **env, int pipefd[2]);

int			second_child(int fd[2], t_cmd *cmd, char **env, int pipefd[2]);

int			ft_echo(t_cmd *cmd1);

int			ft_env(char **env);

int			ft_exit(t_cmd *cmd, t_minishell *minishell);

int			is_builtin(t_cmd *cmd1);

int			exec_builtin(t_cmd *cmd1, t_minishell *minishell);

char		**dup_env(char **env);

int			ft_pwd(t_cmd *cmd);

int			ft_unset(t_cmd *cmd, char ***env);

int			ft_export(t_cmd *cmd1, char ***env);

void		free_minishell(t_minishell *minishell);

char		*ft_substr(char *s, unsigned int start, size_t len);

long long	ft_atoll(const char *nptr);

char		*ft_itoa(int n);

int			is_valid_var_char(char c);

char		*get_var(char *text, int i);

char		*replace_var(char *text, char *expand, char *var, int i);	

int			void_case(char *content);

int			heredoc(char *limiter, t_minishell *minishell, int is_expand);

void		expand_text(t_minishell *minishell, char **text);

int			is_valid_identifier(char *str);

void		handler(int num);

char		**get_path(char **env);

int			identify_token(char *prompt);

char		*token_normal_heredoc(char *content, int *len);

void		expand_variable(t_minishell *minishell, char **text, int *i);

char		*copy_cmd(char *src);

int			check_empty(t_prompt *prompt);

int			count_line(t_prompt *tmp);

void		increment_cmd(t_prompt **prompt, int *i, int *j);

int			check_operand_error(t_prompt *prompt);

void		check_expand(t_minishell *minishell);

int			pipe_cmd(t_minishell *minishell, int nb);

int			check_access(char *path);

void		check_cmd_error(t_minishell *minishell, t_cmd *cmd);

void		dup_io(t_cmd *cmd, int prev_pipe, int pipefd[2], int nb);

void		close_pipe(int *prev_pipe, t_cmd *cmd, int nb, int pipefd[2]);

void		close_fds(t_cmd *cmd);

char		*get_cmd(char *cmd);

void		error_cmd(char *cmd, char *cmd1);

char		*check_file(char *cmd, char *subpath);

char		*check_local(char *cmd1);

char		*goodmalloc(char *s, unsigned int start, size_t len);

void		remove_quotes_from_prompt(t_prompt *prompt);

void		handle_double_quotes(t_minishell *minishell, char **text, int *i);

int			check_heredoc_quotes(char *text);

#endif
