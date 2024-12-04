/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:43:56 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/04 13:24:03 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include<unistd.h>

bool	option_echo(char *str)
{
	int i;

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

int	ft_echo(char **arg, t_env **env)
{
	int i;
	(void)env;

	if (ft_strncmp("echo", arg[0], 7) != 0)
	{
		printf("%s: command not foundsd\n", arg[0]);
		return (0);
	}
	if (!arg[1])
		printf("\n");
	i = 1;
	while (arg[i] && option_echo(arg[i]))
		i++;
	while (arg[i])
	{
		//printf("%d", i);
		printf("%s", arg[i]);
		i++;
		if (arg[i] != NULL)
			printf(" ");
	}
	if (arg[1] && option_echo(arg[1]) == false)
		printf("\n");
	return (0);
}


// int	main(int ac, char **av)
// {
// 	av++;
// 	if (av[0] == NULL && strncmp("echo", av[0], 5) != 0) //mettre ft_strncmp
// 		return (1);
// 	return (echo(av));
// }