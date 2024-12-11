/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:04 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/11 12:53:31 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_main *msh, t_env *env)
{
	(void)env;

	if (ft_strncmp("pwd", msh->cmd_array[0], 4) != 0)
	{
		printf("%s: command not founds\n", msh->cmd_array[0]);
		return (1);
	}
	printf("%s\n", getcwd(NULL, PATH_MAX));
	//perror
	return (0);
}
