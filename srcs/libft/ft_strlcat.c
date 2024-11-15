/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:19 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/23 17:17:13 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	desttaille;
	size_t	srctaille;

	srctaille = ft_strlen(src);
	if (!dest && size == 0)
		return (srctaille);
	i = 0;
	desttaille = ft_strlen(dest);
	j = desttaille;
	if (j >= size)
		return (srctaille + size);
	while (src[i] && i < size - j - 1)
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (srctaille + j);
}
