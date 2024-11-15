/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:22:29 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/29 10:59:11 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nouveau;

	nouveau = malloc(sizeof(t_list));
	if (!nouveau)
		return (NULL);
	nouveau->content = content;
	nouveau->next = NULL;
	return (nouveau);
}
