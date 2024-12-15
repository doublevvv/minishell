/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/12/13 16:56:03 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>

extern int g_signal_global;

enum e_type
{
	PIPE,
	REDIRECTION_IN, // `<`
	REDIRECTION_OUT, // `>`
	REDIRECTION_HEREDOC, // `<<`
	REDIRECTION_APPEND, // `>>`
	WORD
};

enum e_builtin_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_result
{
	ALLOCATION_FAILED,
	UNCLOSED_QUOTE,
	EMPTY_LINE,
	EMPTY_WORD,
	SUCCESS
};

enum e_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};

typedef struct s_lst
{
	int				token_type;
	pid_t			pid;
	union
	{
		char			*word;
		struct s_lst	*cmd_args;
		int				fd;
	} u_data;
	struct s_lst	*next;
}	t_lst;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_size
{
	char	*line;
	int		capacity;
	int		line_size;
}	t_size;

typedef struct s_main
{
	char		*line;
	char		*cmd;
	int			nb_cmd;
	int			nb_cmd_array;
	char		**cmd_array;
	char		**envp;
	char		*env_path;
	char		**paths;
	char		*full_path;
	bool		cmd_valid;
	int			stdin_copy;
	int			stdout_copy;
	int			pipefd[2];
	int			prev_pipe;
	bool		in_pipeline;
	int			file;
	char		*heredoc_filename;
	int			code_status;
	bool		is_exit;
	t_env		*env;
	t_lst		*head_command;
}	t_main;

/* ************************************************************************* */
/*                                 PARSING                                   */
/* ************************************************************************* */

void	ft_init_data(t_main *msh, char **envp);

void	*ft_memset(void *s, int c, size_t n);

void	ft_msh_loop(t_main *msh);

void	ft_init_data_bis(t_main *msh);

bool	ft_check_prompt(t_main *msh, char *str);

int		ft_identify_token(char *str, int *index);

int		ft_get_word(t_main *msh, char *str, int *i);

void	ft_isspace(char *str, int *i);

bool	ft_has_quote(char *str, int *i);

bool	ft_check_quote(char *str, int *i, char c);

/* ************************************************************************* */
/*                                  EXECUTION                                */
/* ************************************************************************* */

void	ft_exec(t_main *msh);

void	ft_handle_exec( t_main *msh, t_lst *cmd, int nb);

void	ft_count_cmds(t_main *msh, t_lst *lst);

void	ft_create_cmd_array(t_main *msh, t_lst *cmd);

void	ft_display_cmd_array(t_main *msh);

void	ft_dup_pipes(t_main *msh, int nb);

void	ft_redirect_pipes(t_main *msh, int old_fd, int new_fd);

void	ft_execute_command(t_main *msh);

void	ft_search_env_path(t_main *msh);

bool	ft_get_paths(t_main *msh);

bool	ft_search_for_slash(t_main *msh);

void	ft_check_access(t_main *msh);

void	ft_check_path(t_main *msh);

void	ft_join_cmd_to_path(t_main *msh, int i);

void	ft_not_in_pipeline(t_main *msh, t_lst *cmd, int builtin);

void	ft_in_pipeline(t_main *msh, t_lst *cmd, int builtin);

void	ft_execute_parent(t_main *msh);

void	ft_final_execution(t_main *msh);

void	ft_parent_wait(t_main *msh);

/* ************************************************************************* */
/*                                     ENV                                   */
/* ************************************************************************* */

t_env	*get_env(char **environ);

t_env	*ft_lstnew_env(char *key, char *value);

void	ft_lstadd_back_env(t_env **lst, t_env *new);

void	lst_env_clear(t_env **lst_env);

void	ft_env(t_env *environ);

char	*ft_join_key_to_value(t_main *msh, t_env *lst_env);

void	ft_convert_env_lst_to_array(t_main *msh);

/* ************************************************************************* */
/*                                   EXPAND                                  */
/* ************************************************************************* */

char	*ft_expand(t_main *msh, char *arg, t_env *env);

char	*interrogation_mark(t_main *msh);

int		check_quotes(char quote, int *index, int *quote_state);

int		comp_var(char *var_name, char *key, int var_size);

int		add_size_to_str(t_size *line, char *str);

int		add_size(t_size *line, char c);

/* ************************************************************************* */
/*                                  BUILT-IN                                 */
/* ************************************************************************* */

int		ft_is_builtin(char *str);

void	ft_execute_builtin(t_main *msh, int i);

int		ft_echo(t_main *msh, t_env *env);

bool	option_echo(char *str);

int		ft_cd(t_main *msh, t_env *env);

int		ft_pwd(t_main *msh, t_env *env);

int		ft_export(t_main *msh, t_env *env);

int		case_sensivity(char *arg);

int		add_var(t_main *msh, char *arg, t_env *env);

t_env	*ft_lstnew_env(char *key, char *value);

void	ft_lstadd_back_env(t_env **lst, t_env *new);

int		ft_unset(t_main *msh, t_env *env);

int		delete_var(char *arg, t_env *head);

void	ft_env(t_env *environ);

int		ft_exit(t_main *msh, t_env *env);

long	ft_atol(char *str);

bool	is_numeric(char *str);

/* ************************************************************************* */
/*                               REDIRECTION                                 */
/* ************************************************************************* */

void	ft_handle_redirections(t_main *msh, t_lst *cmd_args);

void	ft_open_redir(t_main *msh, t_lst *cmd_args);

void	ft_dup_redirections(t_main *msh, int fd_infile, int fd_outfile);

void	ft_close_redirections(int fd_infile, int fd_outfile);

void	ft_generate_random_filename(t_main *msh);

void	ft_read_input_heredoc(char *cmd, int file);

/* ************************************************************************* */
/*                                  LIBFT                                    */
/* ************************************************************************* */

int		ft_printf(int fd, const char *format, ...);

int		ft_putstr(char *s, int fd);

void	ft_putstr_fd(char *str, int fd);

int		ft_putchar_fd(char c, int fd);

int		ft_strlen(const char *str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_substr(char const *s, int start, int len);

int		ft_strcmp(const char *s1, const char *s2);

char	*ft_substr(char const *s, int start, int len);

char	*ft_strnstr(const char *big, const char *little, size_t len);

void	*ft_calloc(size_t count, size_t n);

char	**ft_split(char const *s, char c);

char	*ft_strchr_char(const char *str, int c);

bool	ft_strchr(const char *s, int c);

char	*ft_strjoin(char const *s1, char const *s2);

int		ft_isalpha(int c);

int		ft_isdigit(int c);

char	ft_isalnum(char c);

void	*ft_memcpy(void *dest, const void *src, unsigned int n);

void	ft_bzero(void *s, size_t n);

char	*ft_itoa(int n);

int		ft_count_digit(long int number);

/* ************************************************************************* */
/*                                 LINKED LIST                               */
/* ************************************************************************* */

t_lst	*ft_lstnew(int type, char *name, int file);

void	ft_lstadd_back(t_main *msh, t_lst **lst, t_lst *new);

int		ft_lstsize(t_env *lst);

void	ft_display_lst(t_lst *lst);

bool	ft_verify_lst(t_lst *lst);

/* ************************************************************************* */
/*                                    SIGNAL                                 */
/* ************************************************************************* */

void	sigint_handler(int signal);

void	set_signal(void);

void	here_doc_sig_handler();

/* ************************************************************************* */
/*                                    FREE                                   */
/* ************************************************************************* */

void	ft_print_error_message(int i, char c);

void	ft_print_cmd_msg_error(t_main *msh, int msg);

void	ft_open_file_error(t_main *msh, int fd_infile, int fd_outfile);

void	ft_close_pipes(t_main *msh);

void	ft_close_pipes_child(t_main *msh);

void	ft_free_double_array(char **array);

void	ft_free_lst(t_lst **lst);

void	lst_env_clear(t_env **lst_env);

void	ft_free_all(t_main *msh, char *error, bool is_exit);

#endif