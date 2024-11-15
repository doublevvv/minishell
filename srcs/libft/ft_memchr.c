/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 07:55:52 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/20 17:38:28 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memchr(const void *memblck, int c, size_t n)
{
	char			*blck;
	char			cc;
	unsigned int	i;

	blck = (char *)memblck;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (blck[i] == cc)
			return (blck + i);
		i++;
	}
	return (NULL);
}
