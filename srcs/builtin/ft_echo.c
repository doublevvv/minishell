/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:43:56 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/17 10:07:31 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	option_echo(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(t_main *msh, t_env *env)
{
	int	i;

	i = 1;
	(void)env;
	if (!msh->cmd_array[1])
	{
		if (write(1, "\n", 1) == -1)
		{
			perror("les loutres: echo: write error");
			return (1);
		}
	}
	while (msh->cmd_array[i] && option_echo(msh->cmd_array[i]))
		i++;
	while (msh->cmd_array[i])
	{
		if (write(1, msh->cmd_array[i], ft_strlen(msh->cmd_array[i])) == -1)
		{
			perror("les loutres: echo: write error");
			return (1);
		}
		i++;
		if (msh->cmd_array[i] != NULL)
			write(1, " ", 1);
	}
	if (msh->cmd_array[1] && option_echo(msh->cmd_array[1]) == false)
	{
		if (write(1, "\n", 1) == -1)
		{
			perror("les loutres: echo: write error");
			return (1);
		}
	}
	return (0);
}
