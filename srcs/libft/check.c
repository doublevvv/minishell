/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:47:55 by evlim             #+#    #+#             */
/*   Updated: 2024/10/21 16:04:06 by evlim            ###   ########.fr       */
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

// while (str[i] ) // while white space && !\0
// 	i++;
// while (str[i] ) // while !\0 && !|
// 	i++;
// while (str[i]) // while !\0 && white space
// 	i++;
// int addr = strstr("|") // => si !| return parsing
// // si !:
// while strstr > 0
// {
// 	strstr = addr;
// 	str[strstr]--
// 	if (str[strstr] != whitespace)
// 		return (true);
// 	strstr = addr;
// 	str[strstr]++
// 	if (str[strstr] != whitespace)
// 		return (true);
// }
// bool	ft_is_token(char c)
// {
// 	if (c == '<' || c == '>' || c == '|')
// 		return (true);
// 	return (false);
// 
bool	ft_is_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i - 2] >= 'a' && str[i - 2] <= 'z' && str[i + 2] >= 'a' && str[i + 2] <= 'z')
				return (true);
			else if ((str[i - 2] == '"' || str[i - 2] == '\'') && (str[i + 2] == '"' || str[i + 2] == '\''))
				return (true);
			else if ((str[i - 2] == '"' || str[i - 2] == '\'') || (str[i + 2] == '"' || str[i + 2] == '\''))
				return (true);
			else if (str[i + 2] == '>')
				return (true);
		}
		i++;
	}
	return (false);
}

// int	ft_is_quotes(char c)
// {
// 	if (c == '\'' || c == '"')
// 		return (1);
// 	return (0);
// }

// // int	check_incorrect_signs(char c)
// // {
// // 	if (c != '\'' || c != '"' || c != "|" || c != '>' || c != '<' || c != '$' /
// // 		(c <= 'a' && c >= 'z'))
// // 		return (0);
// // 	return (1);
// // }

// void	ft_free_all(t_main *msh, char *error)
// {
// 	if (pipex->line!= NULL)
// 	{
// 		free(line);
// 	}
// 	exit(1);
// }
