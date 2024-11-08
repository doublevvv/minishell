/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:31:29 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/23 14:20:01 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
