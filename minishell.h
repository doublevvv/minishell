/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:36:57 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/01 14:23:05 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"

typedef	struct t_list
{
	char	**command;
	struct t_list	*next;
}		t_list;

typedef struct l_list
{
	char	**cmd;
	t_list	*linked_list;
}		t_main;

char	display_prompt(char *line);
char	*manage_command(t_main *msh, char *argv);
void	printcmd(t_main *msh);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char **msh);
t_list	*ft_lstlast(t_list *lst);