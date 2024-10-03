/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointeur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:43:26 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/02/23 11:45:42 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	taille(unsigned long long nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

int	pointeur(unsigned long long nb)
{
	if (nb >= 16)
	{
		pointeur(nb / 16);
		pointeur(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + 48);
		else
			ft_putchar(nb - 10 + 'a');
	}
	return (taille(nb));
}

int	ft_pointeur(unsigned long long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
	{
		i = i + write(1, "(nil)", 5);
		return (i);
	}
	i = write(1, "0x", 2);
	i = i + pointeur(nb);
	return (i);
}
