/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:32 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/04 17:15:23 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand(char *arg, t_env **env)
{
	int i;
	t_env *cpy;

	i = 0;
	cpy = *env;
	if (ft_strncmp("$", arg[0], 1) == 0)
	{
		while (cpy)
		{
			if (ft_strstr(cpy->key, arg[i]))
				
		}
	}
	//return string	
}