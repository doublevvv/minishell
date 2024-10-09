/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/10/09 15:01:07 by vlaggoun         ###   ########.fr       */
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

enum type
{
	CMD,
	PIPE,
	REDIRECTION
};

typedef struct s_lst
{
	char			**cmd_name;
	struct s_lst	*next;
	int				type;
}	t_lst;

typedef struct s_main
{
	char	*line;
	char	**cmd;
	bool	double_quote;
	bool	simple_quote;
	int		count;
	t_lst	*cmd_lst;
}	t_main;

void	ft_init_data(t_main *msh);

char	display_prompt(t_main *msh);

void	*ft_memset(void *s, int c, size_t n);

bool	ft_check_quotes(t_main *msh, char *str);

char	**ft_split(char const *s, char c);

int		ft_count_words(char const *str, char delimiter);

void	ft_add_cmd_to_lst(t_main *msh);

void	ft_lstadd_back(t_lst **lst, t_lst *new);

t_lst	*ft_lstnew(char **name);

void	ft_display_lst(t_main *msh);

void	ft_assign_type(t_main *msh);

int	ft_is_quotes(char c);

int	check_incorrect_signs(char c);

int	ft_is_redirection(char *str);

#endif