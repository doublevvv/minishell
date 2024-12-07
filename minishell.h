/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:37:03 by evlim             #+#    #+#             */
/*   Updated: 2024/12/07 14:33:28 by vlaggoun         ###   ########.fr       */
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
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

enum type
{
	CMD,
	PIPE,
	REDIRECTION
};

typedef struct s_size
{
	char *line;
	int	capacity;
	int line_size;
}		t_size;

typedef struct s_env
{
	char *key;
	char *value;
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
	char	**tmp;
	t_lst	*cmd_lst;
	t_env	*env;
}	t_main;

void	ft_init_data(t_main *msh);

char	display_prompt(t_main *msh, t_env *env);

bool	ft_check_quotes(t_main *msh, char *str);

char	**ft_split(char const *s, char c);

int		ft_count_words(char const *str, char delimiter);

void	ft_add_cmd_to_lst(t_main *msh);

void	ft_lstadd_back(t_lst **lst, t_lst *new);

t_lst	*ft_lstnew(char **name);

void	ft_display_lst(t_main *msh);

void	ft_assign_type(t_main *msh);

char	*ft_strnstr(const char *s1, const char *s2, size_t n);


// ***********************************
// *             BUILT_IN            *
// ***********************************

int ft_exit(char **arg, t_env **env);
int	write_error(char **str);
bool	is_numeric(char *str);
long	ft_atol(char *str);
int	ft_cd(char **arg, t_env **env);
t_env	*get_env(char **environ);
void	ft_display_lst_env(t_env *environ);
t_env	*ft_lstnew_env(char *key, char *value);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_add_cmd_to_lst_env(t_env **env, char *key, char *value);
int	old_path( t_env **env, char *old_directory);
int	ft_unset(char **arg, t_env **env);
int	delete_var(char *arg, t_env **head);
int	ft_strcmp(char *s1, char *s2);
int	add_var(char *arg, t_env **env);
int	case_sensivity(char *arg);
int	ft_export(char **arg, t_env **env);
int	ft_echo(char **arg, t_env **env);
int	ft_pwd(char **arg, t_env **env);
// void copy_var(char *src, char *dest, size_t size);

char *ft_expand(char *arg, t_env *env);
int	comp_var(char *var_name, char *key, int var_size);
int	add_size_to_str(t_size *line, char *str);
int	add_size(t_size *line, char c);

#endif