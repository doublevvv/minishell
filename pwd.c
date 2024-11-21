/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:04 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/21 17:24:51 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<limits.h>

void	ft_pwd(char *current_directory)
{	
	printf("%s\n", getcwd(current_directory, PATH_MAX));
	//perror
}
