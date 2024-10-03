/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:10:53 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/07/08 14:59:08 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type(va_list args, const char obj)
{
	int	i;

	i = 0;
	if (obj == 'c')
		i = i + ft_putchar(va_arg(args, int));
	else if (obj == 's')
		i = i + ft_putstr(va_arg(args, char *));
	else if (obj == 'p')
		i = i + ft_pointeur(va_arg(args, unsigned long long));
	else if (obj == 'd' || obj == 'i')
		i = i + ft_putnbr(va_arg(args, int));
	else if (obj == 'u')
		i = i + ft_unsignedint(va_arg(args, unsigned int));
	else if (obj == 'x' || obj == 'X')
		i = i + ft_puthexa(va_arg(args, unsigned int), obj);
	else if (obj == '%')
		i = i + ft_putchar('%');
	return (i);
}

int	ft_printf(const char *obj, ...)
{
	int		i;
	int		n;
	va_list	args;

	i = 0;
	n = 0;
	va_start(args, obj);
	if (obj == NULL)
		return (-1);
	while (obj[n])
	{
		if (obj[n] == '%')
		{
			i = i + type(args, obj[n + 1]);
			n++;
		}
		else
			i = i + ft_putchar(obj[n]);
		n++;
	}
	va_end(args);
	return (i);
}
