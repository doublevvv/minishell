/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:36:14 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/15 16:30:27 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

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
			printf("valeur type = %d\n", tmp->type);
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
	t_lst *new;

	new = ft_lstnew(msh->tmp);
	if (!new)
	{
		//METTRE PLEIN DE PROTECTION
	}
	ft_lstadd_back(&msh->cmd_lst, new);
}
