/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:28:19 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/18 12:46:37 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//#include<stdio.h>
//#include<string.h>

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p++ = (unsigned char)c;
		n--;
	}
	return (s);
}
/*
int	main()
{
	char str[40] = "salut les oiseaux";
	printf("%s", str);
	ft_memset(str, '*', 10);
	printf("\n%s", str);
	return (0);
}
*/
