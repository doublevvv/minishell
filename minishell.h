/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/10/21 16:03:11 by evlim            ###   ########.fr       */
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
	//int				type;
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
	int		type;
	char	*token;
	char	*filename;
	t_lst	*cmd_lst;
}	t_main;

void	ft_init_data(t_main *msh);

void	*ft_memset(void *s, int c, size_t n);

char	ft_display_prompt(t_main *msh, t_redir *lst_redirection);

void	ft_check_prompt(char *str);

bool	ft_check_token(char *str);

bool	ft_is_redirection(char *str);

/* ************************************************************************* */
/*                                  SPLIT                                    */
/* ************************************************************************* */

/* ************************************************************************* */
/*                               LISTES CHAINEES                             */
/* ************************************************************************* */

#endif