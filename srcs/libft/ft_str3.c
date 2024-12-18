/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:25:07 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 09:53:27 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_calloc(size_t count, size_t n)
{
	size_t	i;
	char	*nouvellezone;

	i = 0;
	if (count && n && count > (UINT_MAX / n))
		return (NULL);
	nouvellezone = (char *) malloc(count * n);
	if (!nouvellezone)
		return (NULL);
	while (i < count * n)
	{
		nouvellezone[i] = 0;
		i++;
	}
	return ((void *)nouvellezone);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	ft_isalnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	char			*csrc;
	char			*cdest;
	unsigned int	i;

	csrc = (char *)src;
	cdest = (char *)dest;
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
