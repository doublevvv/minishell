/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/10/11 17:22:52 by evlim            ###   ########.fr       */
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

enum e_type
{
	CMD,
	PIPE,
	REDIRECTION,
	DOUBLE_REDIRECTION,
};

// typedef struct s_redir
// {
// 	char *token; // Type
// 	char *file; // filename
// 	int fd; // fd
// 	struct s_redir	*next; // Liste chainee
// }	t_redir;

// typedef struct s_cmd
// {
// 	char			**cmd; // Command et ses arguments
// 	t_redir	*redir;
// 	struct s_cmd	*next; // Liste chainee
// }	t_cmd;

typedef struct s_lst
{
	char			**cmd_name;
	struct s_lst	*next;
	int				type;
}	t_lst;

typedef struct s_main
{
	char	*line;
	char	**tab_pipe;
	char	**cmd;
	bool	double_quote;
	bool	simple_quote;
	int		token;
	t_lst	*cmd_lst;
}	t_main;

void	ft_init_data(t_main *msh);

char	display_prompt(t_main *msh);

void	*ft_memset(void *s, int c, size_t n);

bool	ft_check_quotes(t_main *msh, char *str);

char	**ft_split_pipe(char const *s, char c);

char	**ft_split_quote(char const *s, char c);

int		ft_count_words(char const *str, char delimiter);

int		ft_count_words_pipe(char const *str, char delimiter);

char	**ft_copy_word(char const *s, char c, char **new_string, int i);

char	**ft_copy_word_pipe(char const *s, char c, char **new_string, int i);

void	*ft_free_alloc(char **new_string, int word);

void	*ft_free_alloc_pipe(char **new_string, int word);

int		ft_word_length(char const *s, char c);

int		ft_word_length_pipe(char const *s, char c);

void	ft_add_cmd_to_lst(t_main *msh);

void	ft_lstadd_back(t_lst **lst, t_lst *new);

t_lst	*ft_lstnew(char **name, int token);

void	ft_display_lst(t_main *msh);

void	ft_assign_type(t_main *msh);

int		ft_is_quotes(char c);

int		check_incorrect_signs(char c);

int		ft_is_redirection(char *str);

#endif