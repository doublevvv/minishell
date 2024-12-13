/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:43:56 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/13 15:00:57 by evlim            ###   ########.fr       */
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
	//	=> A VOIR
	//	if (ft_strncmp("echo", arg[0], 7) != 0)
	// {
	// 	printf("%s: command not foundsd\n", arg[0]);
	// 	return (0);
	// }
	if (!msh->cmd_array[1])
		ft_putstr_fd("\n", 2); //retourner une valeur en cas d'echec d'ecriture
	while (msh->cmd_array[i] && option_echo(msh->cmd_array[i]))
		i++;
	while (msh->cmd_array[i])
	{
		write(1, msh->cmd_array[i], ft_strlen(msh->cmd_array[i])); //retourner une valeur en cas d'echec d'ecriture
		i++;
		if (msh->cmd_array[i] != NULL)
			ft_putstr_fd(" ", 2);  //retourner une valeur en cas d'echec d'ecriture
	}
	if (msh->cmd_array[1] && option_echo(msh->cmd_array[1]) == false)
		ft_putstr_fd("\n", 2); //retourner une valeur en cas d'echec d'ecriture
	return (0);
}
