/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 06:54:41 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/23 14:59:20 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
//#include<string.h>
//#include<stdio.h>

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	char			*csrc;
	char			*cdest;
	unsigned int	i;

	csrc = (char *)src;
	cdest = (char *)dest;
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
/*
int	main()
{
	char str1[] = "gateau";
	char str2[] = "crepes";
	ft_memcpy(str1, str2, sizeof(str2));
	printf("%s", str1);
	return (0);
}
*/
