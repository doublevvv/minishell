/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:16:46 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/11 14:04:30 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_numeric(char *str)
{
	int i;

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
	int		i;
	int		sign;
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
		if (res > LONG_MAX || (res *  sign) < LONG_MIN)
			return (true);
	}
	return (false);
}

int	write_error(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		printf("les loutres: exit: %s: numeric argument required\n", str[i]);
		i++;
	}
	return (0);
} 

int ft_exit(char **arg)
{
	int	exit_code;
	
	if (strncmp("exit", arg[0], 5) != 0)
	{
		printf("%s: command not found\n", arg[0]);
		return (0);
	}
	write(1, "exit1\n", 6);
	exit_code = 0;
	if (arg[1])
	{
		if ((ft_atol(arg[1]) == true))
		{
			exit_code = 2;
			(exit(printf("bash: exit: %s: numeric argument required\n", arg[1])));
		}
		if (is_numeric(arg[1]) == false)
		{
			exit_code = 2;
			exit(write_error(&arg[1]));
		}
		if (arg[1] && arg[2])
		{
			write(2, "bash: exit: too many arguments\n", 31);
			exit_code = 1;
		}
	}
	printf("EXIT_CODE : %d\n", exit_code);
	//ne pas oublier de free
	exit(exit_code);
}
//gerer les cas ou exit est suivi d'un pipe ? 