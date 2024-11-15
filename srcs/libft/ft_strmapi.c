/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:52:17 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/23 15:25:59 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	taille;
	char			*str;

	if (!s)
		return (0);
	i = 0;
	taille = ft_strlen(s);
	str = malloc(sizeof(char) * (taille + 1));
	if (!str)
		return (0);
	while (i < taille)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
