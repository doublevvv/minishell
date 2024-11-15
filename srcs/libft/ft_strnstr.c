/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:09:46 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/23 15:47:19 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
//#include<string.h>
//#include<stdio.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;
	char			*str1;
	char			*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!s1 && n == 0)
		return (0);
	i = ((j = 0));
	if (str2[j] == 0)
		return (&str1[0]);
	j = 0;
	while (str1[i] && i < n)
	{
		j = 0;
		while (str1[i + j] == str2[j] && i + j < n)
		{
			j++;
			if (str2[j] == 0)
				return (&str1[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main()
{
	char haystack[30] = "aaabcabcd";
	//char needle[10] = "aabc";

	printf("%s\n", (ft_strnstr(haystack, "cd", 8)));
	printf("%s\n", (strnstr(haystack, "cd", 8)));
	return (0);
}
*/
