/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/11/18 13:19:29 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

enum type
{
	CMD,
	PIPE,
	REDIRECTION
};

typedef struct s_env
{
	char **key;
	char **value;
	struct s_env *next;
}		t_env;


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
	char	**tmp;
	bool	double_quote;
	bool	simple_quote;
	int		count;
	t_lst	*cmd_lst;
	t_env	*env;
}	t_main;

void	ft_init_data(t_main *msh);

char	display_prompt(t_main *msh);

//void	*ft_memset(void *s, int c, size_t n);

bool	ft_check_quotes(t_main *msh, char *str);

char	**ft_split(char const *s, char c);

int		ft_count_words(char const *str, char delimiter);

void	ft_add_cmd_to_lst(t_main *msh);

void	ft_lstadd_back(t_lst **lst, t_lst *new);

t_lst	*ft_lstnew(char **name);

void	ft_display_lst(t_main *msh);

void	ft_assign_type(t_main *msh);

char	*ft_strnstr(const char *s1, const char *s2, size_t n);

int	ft_strncmp(const char *s1, const char *s2, unsigned int n);


int ft_exit(char **arg);
int	write_error(char **str);
bool	is_numeric(char *str);
long	ft_atol(char *str);
int	ft_cd(char **arg);
char	**get_env(char **environ);
void	ft_display_lst_env(t_main *environ);
t_env	*ft_lstnew_env(char **name);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_add_cmd_to_lst_env(t_main *msh);

#endif