/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:16:46 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/13 14:56:32 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (true);
		i++;
	}
	return (false);
}

long	ft_atol(char *str)
{
	int			i;
	int			sign;
	__int128	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if (res > LONG_MAX || (res * sign) < LONG_MIN)
			return (true);
	}
	return (false);
}

int	write_error(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("les loutres: exit: %s: numeric argument required\n", str[i]);
		i++;
	}
	return (0);
}

int	ft_exit(t_main *msh, t_env *env)
{
	(void)env;
	int	exit_code;
//ecire exit sur sorti d'erreur et ne pas ecrire exit si pas dans un tty (terminal)
	//A VOIR
	if (strncmp("exit", msh->cmd_array[0], 5) != 0)
	{
		printf("%s: command not found\n", msh->cmd_array[0]);
		return (0);
	}
	write(2, "exit1\n", 6);
	exit_code = 0;
	if (msh->cmd_array[1])
	{
		if ((ft_atol(msh->cmd_array[1]) == true))
		{
			exit_code = 2;
			ft_free_all(msh, NULL, true);
			ft_printf(2, "les loutres: exit: %s: numeric argument required\n", msh->cmd_array[1]);
			exit(2);
		}
		if (is_numeric(msh->cmd_array[1]) == false)
		{
			exit_code = 2;
			ft_free_all(msh, NULL, true);
			exit(write_error(&msh->cmd_array[1]));
		}
		if (msh->cmd_array[1] && msh->cmd_array[2])
		{
			write(2, "les loutres: exit: too many arguments\n", 39);
			exit_code = 1;
		}
	}
	else
	{
		exit(msh->code_status);	
	}
	printf("EXIT_CODE : %d\n", exit_code);
	ft_free_all(msh, NULL, true);
	return (exit_code);
}
//gerer les cas ou exit est suivi d'un pipe ? 
