/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:28:50 by evlim             #+#    #+#             */
/*   Updated: 2024/12/19 09:50:44 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lst	*ft_lstnew(int type, char *name, int file)
{
	t_lst	*new_node;

	new_node = malloc(sizeof(t_lst));
	if (!new_node)
		return (NULL);
	new_node->token_type = type;
	new_node->pid = -1;
	new_node->u_data.word = name;
	if (new_node->token_type == REDIRECTION_HEREDOC)
	{
		new_node->u_data.fd = file;
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_main *msh, t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (!new)
	{
		free(msh->cmd);
		ft_free_all(msh, NULL, true);
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

bool	ft_verify_lst(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*tmp_arg;

	tmp = lst;
	while (tmp != NULL)
	{
		tmp_arg = tmp->u_data.cmd_args;
		if (tmp_arg == NULL)
		{
			return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

int	ft_lstsize(t_env *lst)
{	
	int	number_elements;

	if (!lst)
	{
		return (0);
	}
	number_elements = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		number_elements++;
	}
	return (number_elements);
}

// void	ft_display_lst(t_lst *lst)
// {
// 	int		i;
// 	t_lst	*tmp;
// 	t_lst	*tmp_arg;

// 	i = 0;
// 	tmp = lst;
// 	dprintf(2, "-------------------------------------------\n");
// 	dprintf(2, "DANS LISTE\n");
// 	while (tmp != NULL)
// 	{
// 		tmp_arg = tmp->u_data.cmd_args;
// 		dprintf(2, "Node %d\n", i);
// 		while (tmp_arg != NULL)
// 		{
// 			dprintf(2, "-----\n");
// 			dprintf(2, "token type: %d\n", tmp_arg->token_type);
// 			dprintf(2, "pid: %d\n", tmp_arg->pid);
// 			if (tmp_arg->token_type == REDIRECTION_HEREDOC)
// 			{
// 				dprintf(2, "fd: %d\n", tmp_arg->u_data.fd);
// 			}
// 			else
// 			{
// 				dprintf(2, "u_data->word: %s\n", tmp_arg->u_data.word);
// 			}
// 			tmp_arg = tmp_arg->next;
// 		}
// 		dprintf(2, "-------------------------\n");
// 		i++;
// 		tmp = tmp->next;
// 	}
// }
