/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:59:46 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/11/08 14:03:56 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<ctype.h>

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	else
		return (0);
}