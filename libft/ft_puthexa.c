/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:46:03 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/02/22 16:38:27 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	taillehexa(unsigned int nb)
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

void	hexa(unsigned int nb, const char obj)
{
	if (nb >= 16)
	{
		hexa(nb / 16, obj);
		hexa(nb % 16, obj);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + 48);
		else
		{
			if (obj == 'x')
				ft_putchar(nb - 10 + 'a');
			if (obj == 'X')
				ft_putchar(nb - 10 + 'A');
		}
	}
}

int	ft_puthexa(unsigned int nb, const char obj)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		hexa(nb, obj);
	return (taillehexa(nb));
}
