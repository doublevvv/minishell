/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:21:07 by evlim             #+#    #+#             */
/*   Updated: 2024/12/17 10:03:28 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
	{
		return ;
	}
	write(fd, str, ft_strlen(str));
}

int	ft_putstr(char *s, int fd)
{
	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	else
	{
		ft_putstr_fd((char *)s, fd);
	}
	return (ft_strlen((char *)s));
}

static int	ft_print_format(va_list args, const char specifier, int fd)
{
	int	length;

	length = 0;
	if (specifier == 'c')
	{
		length += ft_putchar_fd(va_arg(args, int), fd);
	}
	else if (specifier == 's')
	{
		length += ft_putstr(va_arg(args, char *), fd);
	}
	return (length);
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		length;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = 0;
	length = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			length += ft_print_format(args, format[i + 1], fd);
			i++;
		}
		else
			length += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (length);
}
