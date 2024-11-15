/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:18:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/20 08:52:15 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
#include<string.h>

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
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
/*
int	main(void)
{
	printf("\n\n=========== TESTING STRCHR ============\n\n");

        char *str = "tripouille";
        printf("%s\n", (ft_strchr(str, 't'+ 256)));
	printf("%s\n", (strchr(str, 't' + 256)));
        return (0);
}
*/
