/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:25:39 by evlim             #+#    #+#             */
/*   Updated: 2024/12/16 10:49:52 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* First, the ft_join_cmd_to_path() function appends a `/` character,
then the command name to the end of each path. */
void	ft_join_cmd_to_path(t_main *msh, int i)
{
	char	*path_tmp;

	path_tmp = ft_strjoin(msh->paths[i], "/");
	if (!path_tmp)
	{
		ft_putstr_fd("Failed to join\n", 2);
		ft_free_all(msh, NULL, true);
	}
	msh->full_path = ft_strjoin(path_tmp, msh->cmd_array[0]);
	if (!msh->full_path)
	{
		if (path_tmp)
		{
			free(path_tmp);
			path_tmp = NULL;
		}
		ft_free_double_array(msh->cmd_array);
	}
	free(path_tmp);
}

void	ft_print_cmd_msg_error(t_main *msh, int msg)
{
	if (msg == 1)
	{
		ft_printf(2, "%s: command not found\n", msh->cmd_array[0]);
	}
	else if (msg == 2)
	{
		ft_printf(2, "%s: Permission denied\n", msh->cmd_array[0]);
	}
}

/* The ft_check_path() function searches for the command in the paths of
the `PATH` environment and checks whether the command exists and 
is executable. */
void	ft_check_path(t_main *msh)
{
	int	i;

	i = 0;
	while (msh->paths[i] != NULL)
	{
		ft_join_cmd_to_path(msh, i);
		if (access(msh->full_path, F_OK) == 0)
		{
			if (access(msh->full_path, X_OK) == 0)
			{
				msh->cmd_valid = 1;
				break ;
			}
			else
			{
				ft_print_cmd_msg_error(msh, 2);
				ft_free_all(msh, NULL, false);
				exit(126);
			}
		}
		free(msh->full_path);
		i++;
	}
	if (msh->paths[i] == NULL)
	{
		ft_print_cmd_msg_error(msh, 1);
		ft_free_all(msh, NULL, false);
		if (msh->env != NULL)
		{
			lst_env_clear(&msh->env);
		}
		exit(127);
	}
}

/* In the ft_check_access() function, if the command is a full path, it checks
whether the command exists and is executable. */
void	ft_check_access(t_main *msh)
{
	//si commnd[0] == '\0' command not found et parti ??????????
	if (access(msh->full_path, F_OK) == 0)
	{
		if (access(msh->full_path, X_OK) == 0)
		{
			msh->cmd_valid = 1;
		}
		else
		{
			ft_print_cmd_msg_error(msh, 2);
			ft_free_all(msh, NULL, false);
			exit(126);
		}
	}
	else
	{
		ft_print_cmd_msg_error(msh, 1);
		ft_free_all(msh, NULL, false);
		if (msh->env != NULL)
		{
			lst_env_clear(&msh->env);
		}
		exit(127);
	}
}
