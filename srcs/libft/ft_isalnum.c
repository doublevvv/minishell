/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:50:29 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/08 13:20:42 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
#include<unistd.h>
#include<stdio.h>
#include<ctype.h>

char	ft_isalnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
/*
int	main()
{
	char c, result;

	c = '/';
	result = ft_isalnum(c);
	printf("%d", result);
	return (0);
}
*/
