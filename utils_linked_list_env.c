/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:54:35 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/29 15:36:05 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_lst_env(t_env *environ)
{
	(void)environ;
	t_env	*cpy;

	cpy = environ;
	printf("DANS LISTE\n");
	while (cpy != NULL)
	{
		printf("KEY : |%s|\n",cpy->key);
		printf(" VALUE : |%s|\n", cpy->value);
		cpy = cpy->next;
	}
	printf("----------------------------------\n");
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;
	
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
