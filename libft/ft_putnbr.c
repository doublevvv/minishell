/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:37:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/02/22 16:39:13 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

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
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		sign = -sign;
	}
	if (n == 0)
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

int	ft_putnbr(int nb)
{
	char	*str;
	int		taille;

	str = ft_itoa(nb);
	taille = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (taille);
}
