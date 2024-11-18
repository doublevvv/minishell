/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:54:35 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/18 17:21:55 by vlaggoun         ###   ########.fr       */
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
		while (tmp->key != NULL && tmp->value != NULL)
		{
			printf("%d | %s\n", i, tmp->key);
			printf("%d | %s\n", i, tmp->value);
			//printf("valeur type = %d\n", tmp->key);
			i++;
			j++;
		}
		tmp = tmp->next;
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
	printf("HEREee\n");
	if (!*lst)
	{
		printf("HER\n");
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