/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:31:46 by vlaggoun          #+#    #+#             */
/*   Updated: 2023/12/15 08:51:08 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*t;

	i = 0;
	t = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			t = ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		t = ((char *)&str[i]);
	return (t);
}
/*
int     main(void)
{
        printf("\n\n=========== TESTING STRCHR ============\n\n");

        char str[] = "tripouille";
	char s2[] = "ltripouiel";
        printf("%s\n", (ft_strrchr(s2, '1')));
        printf("%s\n", (strrchr(s2, '1')));
        return (0);
}
*/
