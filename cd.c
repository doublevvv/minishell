/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:39:45 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/12 14:18:46 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av)
// {
// 	char s[1000];
// 	// if (ac != X)
// 	// 	ft_putendl_fd();	
// 	if (chdir(av[1]) == -1)
// 		perror("cd");
// 	if ()
	
// 	printf("%s\n", getcwd(s, PATH_MAX));
// }

// void	ft_cd(char *path)
// {
// 	char *current_directory;
	
// 	path = getcwd(current_directory, PATH_MAX);
// 	chdir(path);
// 	if (chdir(path) == -1)
// 	{
// 		perror("Error ");
// 	}
	
// }

// void	cd_error(char *str)
// {
	
// }

int	ft_cd(char **arg)
{
	char *home;
	
	home = NULL;
	if (strncmp("cd", arg[0], 3) != 0)
	{
		printf("%s: command not found\n", arg[0]);
		return (0);
	}
	if (arg[0] && !arg[1])
	{
		if (!home)
		{
			printf("les loutres: cd: HOME not set\n");
			return (0);
		}
	}
	if (arg[1])
	{
		if (chdir(arg[1]) == -1)
			return(printf("les loutres: cd: %s: No such file or directory\n", arg[1]));
		if (arg[1] && arg[2])
		{
			write(1, "les loutres: cd: too many arguments\n", 37);
			return (0);
		}	
	}
	return (0);
}