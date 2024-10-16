/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:47:55 by evlim             #+#    #+#             */
/*   Updated: 2024/10/16 10:45:09 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

int	ft_is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (!big)
		return (NULL);
	if (*little == '\0')
		return ((char *)(big));
	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] && little[j] != '\0'
			&& big[i + j] == little[j])
		{
			j++;
		}
		if (little[j] == '\0')
		{
			return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
// int	ft_is_redirection(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '>' || str[i] == '<')
// 		{
// 			if (str[i - 2] >= 'a' && str[i - 2] <= 'z' && str[i + 2] >= 'a' && str[i + 2] <= 'z')
// 				return (1);
// 			else if ((str[i - 2] == '"' || str[i - 2] == '\'') && (str[i + 2] == '"' || str[i + 2] == '\''))
// 				return (1);
// 			else if ((str[i - 2] == '"' || str[i - 2] == '\'') || (str[i + 2] == '"' || str[i + 2] == '\''))
// 				return (1);
// 			else if (str[i] == '<' && str[i + 1] == '<')
// 				return (1);
// 			else if (str[i] == '>' && str[i + 1] == '>')
// 				return (1);
// 			else
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }
