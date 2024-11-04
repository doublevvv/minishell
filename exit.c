/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:16:46 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:47 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


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


int ft_exit(char *arg)
{
	int	exit_code;
	
	// if (!arg[1])
	// {
	// 	exit_code = 0;
	// 	printf("NOARG\n");
	// }
	if (arg[1])
	{
		if (is_numeric(&arg[1]) == false)
		{
			exit_code = 2;
			printf("exit\n");
			printf("les loutres: exit: %c: numeric argument required\n", arg[1]);
		}
		if (!arg[1] && arg[2])
		{
			exit_code = 1;
			printf("les loutres: exit: too many arguments\n");
		}
	}
	return (0);
}

	int	main(int ac, char **av)
{
	av++;
	int i = 1;
	if (av[0] == NULL && strncmp("exit", av[0], 5) != 0) //mettre ft_strncmp
		return (1);
	if (av[0] && !av[1])
		printf("exit\n");
	while (av[i])
	{
		ft_exit(av[i]);
		i++;
	}
	return (0);
}

typedef struct s_list
{
	int	exit_code;
	char	**cmd;
	
}		t_list;
