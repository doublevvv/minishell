/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:46:00 by evlim             #+#    #+#             */
/*   Updated: 2024/10/16 11:18:01 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_display_lst(t_main *msh)
{
	int		i;
	t_lst	*tmp;

	tmp = msh->cmd_lst;
	printf("DANS LISTE\n");
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->cmd_name[i] != NULL)
		{
			printf("%d | %s\n", i, tmp->cmd_name[i]);
			i++;
		}
		tmp = tmp->next;
	}
	printf("----------------------------------\n");
}

t_lst	*ft_lstnew(char **name)
{
	t_lst	*new_node;

	new_node = malloc(sizeof(t_lst));
	if (!new_node)
		return (NULL);
	new_node->cmd_name = name;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (!new)
	{
		//free
	}
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	ft_add_cmd_to_lst(t_main *msh)
{
	ft_lstadd_back(&msh->cmd_lst, ft_lstnew(msh->cmd));
}

// // int	check_incorrect_signs(char c)
// // {
// // 	if (c != '\'' || c != '"' || c != "|" || c != '>' || c != '<' || c != '$' /
// // 		(c <= 'a' && c >= 'z'))
// // 		return (0);
// // 	return (1);
// // }

void	ft_lstadd_back_redir(t_redir **lst_redirection, t_redir *new)
{
	t_redir	*tmp;

	if (!new)
	{
		//free
	}
	if (!*lst_redirection)
	{
		*lst_redirection = new;
		return ;
	}
	if (*lst_redirection)
	{
		tmp = *lst_redirection;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}
t_redir	*ft_lstnew_redir(char *name)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (NULL);
	printf("AVANT name = %s\n", name);
	new_node->token = name;
	printf("new_node token = %s\n", new_node->token);
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_redirection_to_lst(t_redir *lst_redirection)
{
	ft_lstadd_back_redir(&lst_redirection, ft_lstnew_redir(lst_redirection->token));
}

void	ft_display_lst_redir(t_redir *lst_redirection)
{
	int		i;
	t_redir	*tmp;

	tmp = lst_redirection;
	printf("DANS LISTE REDIRECTION\n");
	while (tmp != NULL)
	{
		i = 0;
		printf("DANS LISTE %s\n", tmp->token);
		tmp = tmp->next;
	}
	printf("----------------------------------\n");
}
