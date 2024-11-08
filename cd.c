/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:39:45 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/28 15:11:07 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<limits.h>

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

void	ft_cd(char *path)
{
	char *current_directory;
	
	path = getcwd(current_directory, PATH_MAX);
	chdir(path);
	if (chdir(path) == -1)
	{
		perror("Error ");
	}
	
}

int main()
{
	char str[1000];
	ft_cd(str);
}