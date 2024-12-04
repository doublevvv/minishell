/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:04 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/04 13:22:10 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **arg, t_env **env)
{
	(void)env; 
	
	if (ft_strncmp("pwd", arg[0], 4) != 0)
	{
		printf("%s: command not foundsg\n", arg[0]);
		return (1);
	}
	printf("%s\n", getcwd(NULL, PATH_MAX));
	//perror
	return (0);
}
