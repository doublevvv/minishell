/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:05:47 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/23 15:55:37 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	int		n;
	char	*nouvellechaine;

	if (!s1 || !s2)
		return (0);
	n = ft_strlen(s1) + ft_strlen(s2);
	nouvellechaine = malloc((n + 1) * sizeof(char));
	if (!nouvellechaine)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i])
		nouvellechaine[k++] = s1[i++];
	j = 0;
	while (s2[j])
		nouvellechaine[k++] = s2[j++];
	nouvellechaine[k] = '\0';
	return (nouvellechaine);
}
/*
int	main()
{
	char str[] = "tarte";
	char sti[] = "pommes";
	printf("%s\n", ft_strjoin(str, sti));
	return (0);
}
*/
