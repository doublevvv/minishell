/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/10/17 16:11:41 by evlim            ###   ########.fr       */
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
	REDIRECTION_LEFT,
	REDIRECTION_RIGHT,
	DOUBLE_REDIRECTION_LEFT,
	DOUBLE_REDIRECTION_RIGHT
};

typedef struct s_redir
{
	char			*token;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

// typedef struct s_cmd
// {
// 	char			**cmd; // Commande et ses arguments
// 	t_redir	*redir;
// 	struct s_cmd	*next; // Liste chainee
// }	t_cmd;

typedef struct s_lst
{
	char			**cmd_name;
	t_redir			*redir;
	struct s_lst	*next;
}	t_lst;

typedef struct s_main
{
	char	*line;
	char	**tab_pipe;
	char	**cmd;
	char	**redirection_filename;
	bool	double_quote;
	bool	simple_quote;
	char	*redir;
	char	*token;
	char	*filename;
	t_lst	*cmd_lst;
}	t_main;

void	ft_init_data(t_main *msh);

void	*ft_memset(void *s, int c, size_t n);

char	display_prompt(t_main *msh, t_redir *lst_redirection);

int		check_prompt(char *str);

bool	ft_check_quotes(t_main *msh, char *str);

int		ft_is_quotes(char c);

//int		ft_isspace(char c);

char	*ft_strstr(const char *big, const char *little);

void	ft_check_redirection(t_main *msh, t_redir **lst_redirection);

void	ft_redir_sep(t_redir *lst_redirection);

//void	ft_assign_type(t_main *msh);

/* ************************************************************************* */
/*                                  SPLIT                                    */
/* ************************************************************************* */

char	**ft_split_pipe(char const *s, char c);

int		ft_count_words_pipe(char const *str, char delimiter);

int		ft_word_length_pipe(char const *s, char c);

void	*ft_free_alloc_pipe(char **new_string, int word);

char	**ft_copy_word_pipe(char const *s, char c, char **new_string);

char	**ft_split_redir(char const *s, char delimiter);

int		ft_count_words_redir(char const *str, char delimiter);

int		ft_word_length_redir(char const *s, char delimiter);

char	**ft_copy_word_redir(char const *s, char delimiter, char **new_string, int i);

void	*ft_free_alloc_redir(char **new_string, int word);

/* ************************************************************************* */
/*                               LISTES CHAINEES                             */
/* ************************************************************************* */

void	ft_add_cmd_to_lst(t_main *msh);

t_lst	*ft_lstnew(char **name);

void	ft_lstadd_back(t_lst **lst, t_lst *new);

void	ft_display_lst(t_main *msh);

void	ft_add_redirection_to_lst(t_main *msh, t_redir **lst_redirection);

t_redir	*ft_lstnew_redir(char *name, char *filename);

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new);

void	ft_display_lst_redir(t_redir *lst_redirection);

#endif