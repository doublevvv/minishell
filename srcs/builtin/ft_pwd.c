/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:01:04 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 09:10:10 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_main *msh, t_env *env)
{
	(void)env;
	(void)msh;

	char *ptr;

	ptr = getcwd(NULL, PATH_MAX);
	if (!ptr)
		write(2, "les loutres: path doesn't exist\n", 32);
	else if (printf("%s\n", ptr) == -1)
	{
		free(ptr);
		return (1);
	}
	free(ptr);
	return (0);
}
