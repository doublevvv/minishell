/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:49:33 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/20 17:36:24 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	char			*csrc;
	char			*cdest;
	unsigned int	i;

	csrc = (char *)src;
	cdest = (char *)dest;
	i = 0;
	if (!csrc && !cdest)
		return (NULL);
	if (cdest < csrc)
	{
		while (i < n)
		{
			cdest[i] = csrc[i];
			i++;
		}
	}
	while (i < n)
	{	
		cdest[n - 1 - i] = csrc[n - 1 - i];
		i++;
	}
	return (dest);
}
/*
int	main()
{
	char csrc[] = "tartepommes";
	ft_memmove(csrc + 2, csrc, sizeof(csrc));
	printf("%s", csrc);
	return (0);
}
*/
