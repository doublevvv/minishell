/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:06:23 by evlim             #+#    #+#             */
/*   Updated: 2024/12/18 09:53:35 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big)
		return (NULL);
	if (*little == '\0')
		return ((char *)(big));
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] && little[j] != '\0'
			&& (i + j) < len && big[i + j] == little[j])
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

bool	ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

int	ft_count_digit(long int number)
{
	int	digit;

	digit = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number = number * (-1);
		digit++;
	}
	while (number > 0)
	{
		number = number / 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	int			digit_counter;
	long int	nb;
	char		*dest;

	nb = n;
	digit_counter = ft_count_digit(nb);
	dest = malloc((digit_counter + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[digit_counter] = '\0';
	if (nb < 0)
		nb = nb * (-1);
	while (digit_counter - 1 >= 0)
	{
		dest[digit_counter - 1] = (nb % 10) + '0';
		nb = nb / 10;
		digit_counter--;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}
