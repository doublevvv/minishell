/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:25:07 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/23 12:00:07 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	size_t	i;
	char	*nouvellezone;

	i = 0;
	if (count && n && count > (UINT_MAX / n))
		return (NULL);
	nouvellezone = (char *) malloc(count * n);
	if (!nouvellezone)
		return (NULL);
	while (i < count * n)
	{
		nouvellezone[i] = 0;
		i++;
	}
	return ((void *)nouvellezone);
}
//INT MAX ??? 
