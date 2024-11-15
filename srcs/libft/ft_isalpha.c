/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:00:44 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/08 13:22:09 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
#include<unistd.h>
#include<stdio.h>
#include<ctype.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
/*
int	main()
{
	char c, result;

	c = 'h';
	result = ft_isalpha(c);
	printf("%d", result);
	return (0);
}
*/
