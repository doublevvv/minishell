/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:47:55 by evlim             #+#    #+#             */
/*   Updated: 2024/12/12 12:54:44 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
	{
		return ;
	}
	write(fd, str, ft_strlen(str));
}

void	ft_isspace(char *str, int *i)
{
	while (str[*i] != '\0' && (str[*i] == ' ' || str[*i] == '\t'))
	{
		(*i)++;
	}
}

bool	ft_check_quote(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
	{
		(*i)++;
	}
	if (str[*i] == '\0')
	{
		return (false);
	}
	return (true);
}

bool	ft_has_quote(char *str, int *i)
{
	char	c;

	if (str[*i] == '"')
	{
		c = '"';
		if (ft_check_quote(str, i, c) == 0)
		{
			return (false);
		}
	}
	else if (str[*i] == '\'')
	{
		c = '\'';
		if (ft_check_quote(str, i, c) == 0)
		{
			return (false);
		}
	}
	return (true);
}
