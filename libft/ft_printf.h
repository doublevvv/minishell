/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:45:07 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/07/08 15:00:00 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_pointeur(unsigned long long nb);
int		ft_printf(const char *obj, ...);
int		ft_putchar(char c);
int		ft_puthexa(unsigned int nb, const char obj);
int		ft_putnbr(int nb);
int		ft_putstr(char *str);
int		ft_unsignedint(unsigned int nb);
size_t	ft_strlen(char const *str);

#endif
