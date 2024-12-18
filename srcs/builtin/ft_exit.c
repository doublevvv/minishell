/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:16:46 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 11:55:35 by evlim            ###   ########.fr       */
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

bool	ft_overflow(char *str)
{
	int					i;
	int					sign;
	long long int						res;

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
		if ((res * sign) > 2147483647 || (res * sign) < -2147483648)
			return (true);
	}
	return (false);
}

void	ft_is_numeric(t_main *msh)
{
	if (is_numeric(msh->cmd_array[1]) == false)
	{
		ft_printf(2, "les loutres: exit: %s: numeric argument required\n",
			msh->cmd_array[1]);
		ft_free_all(msh, NULL, false);
		exit(2);
	}
}

int	ft_exit(t_main *msh, t_env *env)
{
	int	exit_code;

	(void)env;
	write(2, "exit1\n", 6);
	exit_code = 0;
	if (msh->cmd_array[1])
	{
		is_overflow(msh);
		ft_is_numeric(msh);
		if (msh->cmd_array[1] && msh->cmd_array[2])
			return (write(2, "les loutres: exit: too many arguments\n", 39), 1);
		else
		{
			exit_code = ft_atoi(msh->cmd_array[1]);
			ft_free_all(msh, NULL, false);
			exit((unsigned char)exit_code);
		}
	}
	else
	{
		ft_free_all(msh, NULL, true);
		exit(msh->code_status);
	}
	return (exit_code);
}
