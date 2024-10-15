/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/10/15 17:32:53 by evlim            ###   ########.fr       */
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
// 	char			**cmd; // Commande et ses arguments
// 	t_redir	*redir;
// 	struct s_cmd	*next; // Liste chainee
// }	t_cmd;

// typedef struct s_lst
// {
// 	char			**cmd_name;
// 	int				type;
// 	struct s_lst	*next;
// }	t_lst;

typedef struct s_main
{
	char	*line;
	char	**tab_pipe;
	//char	**cmd;
	bool	double_quote;
	bool	simple_quote;
	//int		token;
	//t_lst	*cmd_lst;
}	t_main;

void	ft_init_data(t_main *msh);

void	*ft_memset(void *s, int c, size_t n);

char	display_prompt(t_main *msh);

int		check_prompt(char *str);

bool	ft_check_quotes(t_main *msh, char *str);

int		ft_is_quotes(char c);

char	**ft_split_pipe(char const *s, char c);

int		ft_count_words_pipe(char const *str, char delimiter);

int		ft_word_length_pipe(char const *s, char c);

void	*ft_free_alloc_pipe(char **new_string, int word);

char	**ft_copy_word_pipe(char const *s, char c, char **new_string, int i);

#endif