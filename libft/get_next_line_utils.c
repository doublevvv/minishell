/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:44:47 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/08/20 13:48:32 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char const *str, int c)
{
	size_t	i;

	i = 0;
	if (!str || !c)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&str[i]);
	else
		return (NULL);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i + 1] = src[i];
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	int		n;
	char	*nouvellechaine;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	n = ft_strlen(s1) + ft_strlen(s2);
	nouvellechaine = malloc(sizeof(char) * (n + 1));
	if (!nouvellechaine || !s2)
		return (free(s1), NULL);
	i = 0;
	k = 0;
	while (s1[i])
		nouvellechaine[k++] = s1[i++];
	j = 0;
	while (s2[j])
		nouvellechaine[k++] = s2[j++];
	nouvellechaine[k] = '\0';
	free(s1);
	return (nouvellechaine);
}

// char	*ft_strchr(const char *str, int c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == (char)c)
// 			return ((char *)&str[i]);
// 		i++;
// 	}
// 	if (c == 0)
// 		return ((char *)&str[i]);
// 	else
// 		return (NULL);
// }