/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:35:25 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/02/22 16:39:55 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;
	int	j;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = ft_strlen(str);
	j = 0;
	while (str[j])
	{
		write(1, &str[j], 1);
		j++;
	}
	return (i);
}
