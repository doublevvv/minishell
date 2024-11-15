/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:11:33 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/20 17:23:05 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	premier;
	size_t	drnr;
	char	*nouvellechaine;

	nouvellechaine = 0;
	if (s1 != 0 && set != 0)
	{
		premier = 0;
		drnr = ft_strlen(s1);
		while (s1[premier] && ft_strchr(set, s1[premier]))
			premier++;
		while (s1[drnr - 1] && ft_strchr(set, s1[drnr - 1]) && drnr > premier)
			drnr--;
		nouvellechaine = malloc(sizeof(char) * (drnr - premier + 1));
		if (nouvellechaine)
			ft_strlcpy(nouvellechaine, &s1[premier], drnr - premier + 1);
	}
	return (nouvellechaine);
}
