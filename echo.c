/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:43:56 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/24 08:17:15 by vlaggoun         ###   ########.fr       */
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

int	echo(char **argv)
{
	int i;
	
	i = 1;
	while (argv[i] && option_echo(argv[i]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i] != NULL)
			printf(" ");
	}
	if (argv[1] && option_echo(argv[1]) == false)
		printf("\n");
	return (0);
}


int	main(int ac, char **av)
{
	av++;
	if (av[0] == NULL && strncmp("echo", av[0], 5) != 0) //mettre ft_strncmp
		return (1);
	return (echo(av));
}