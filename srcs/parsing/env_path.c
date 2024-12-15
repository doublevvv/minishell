/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:29:45 by evlim             #+#    #+#             */
/*   Updated: 2024/11/19 16:53:32 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* The ft_search_env_path() function searches for the `PATH` environement
variable stored in the env linked list. */
void	ft_search_env_path(t_main *msh)
{
	int	i;

	i = 0;
	while (msh->envp[i] != NULL)
	{
		msh->env_path = ft_strnstr(msh->envp[i], "PATH=", 5);
		if (msh->env_path != NULL)
		{
			break ;
		}
		i++;
	}
	if (msh->envp[i] == NULL)
	{
		msh->env_path = "NOENV";
	}
}

/* The ft_get_paths() function splits the `PATH` value into individual paths 
and stores them in `msh->paths`. */
bool	ft_get_paths(t_main *msh)
{
	msh->paths = ft_split(&msh->env_path[5], ':');
	if (!msh->paths)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		return (false);
	}
	return (true);
}
