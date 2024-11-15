/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:02:56 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/23 14:29:05 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
#include<string.h>
#include <limits.h>

size_t	nbrchiffre(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	long	sign;
	char	*result;

	sign = n;
	i = nbrchiffre(n);
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	if (sign < 0)
	{
		result[0] = '-';
		sign = -sign;
	}
	if (sign == 0)
		result[0] = '0';
	result[i--] = '\0';
	while (sign)
	{
		result[i] = sign % 10 + '0';
		i--;
		sign = sign / 10;
	}
	return (result);
}
