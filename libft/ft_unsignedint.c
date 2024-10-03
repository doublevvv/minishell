/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:08:07 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/02/23 09:21:16 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	taille(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char	*intstr(unsigned int nb)
{
	char	*str;
	int		i;

	i = taille(nb);
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (nb != 0)
	{
		str[i - 1] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	return (str);
}

int	ft_unsignedint(unsigned int nb)
{
	char	*str;
	int		i;

	i = 0;
	if (nb == 0)
		i = i + write(1, "0", 1);
	else
	{
		str = intstr(nb);
		i = ft_strlen(str);
		ft_putstr(str);
		free(str);
	}
	return (i);
}
