/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:57:53 by evlim             #+#    #+#             */
/*   Updated: 2024/12/12 16:20:38 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*sub_string;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	sub_string = malloc((len + 1) * sizeof(char));
	if (!sub_string)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && start < ft_strlen(s))
	{
		sub_string[j] = s[i];
		i++;
		j++;
	}
	sub_string[j] = '\0';
	return (sub_string);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
