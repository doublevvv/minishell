/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:54:35 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/18 13:01:57 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_lst_env(t_main *environ)
{
	int		i;
	int		j;
	t_env	*tmp;

	tmp = environ->env;
	printf("DANS LISTE\n");
	while (tmp != NULL)
	{
		i = 0;
		j = 0;
		while (tmp->key[i] != NULL && tmp->value[j] != NULL)
		{
			printf("%d | %s\n", i, tmp->key[i]);
			printf("%d | %s\n", i, tmp->value [i]);
			//printf("valeur type = %d\n", tmp->key);
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	printf("----------------------------------\n");
}

t_env	*ft_lstnew_env(char **name)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = name;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

void	ft_add_cmd_to_lst_env(t_main *msh)
{
	t_main *new;

	new = ft_lstnew(msh->tmp);
	if (!new)
	{
		//METTRE PLEIN DE PROTECTION
	}
	ft_lstadd_back(&msh->env, new);
}