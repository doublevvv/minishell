/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:25:39 by evlim             #+#    #+#             */
/*   Updated: 2024/12/19 09:50:36 by evlim            ###   ########.fr       */
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
		ft_putstr_fd("Failed to join `/` to path\n", 2);
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
		ft_putstr_fd("Failed to join command to path\n", 2);
		ft_free_all(msh, NULL, true);
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

void	ft_path_not_found(t_main *msh, int i)
{
	if (msh->paths[i] == NULL)
	{
		ft_print_cmd_msg_error(msh, 1);
		ft_free_all(msh, NULL, false);
		if (msh->env != NULL)
		{
			lst_env_clear(&msh->env);
		}
		//dprintf(2, "NO PATH Command not found\n");
		msh->code_status = 127;
		exit(msh->code_status);
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
				//dprintf(2, "NO PATH Permission denied\n");
				msh->code_status = 126;
				exit(msh->code_status);
			}
		}
		free(msh->full_path);
		i++;
	}
	ft_path_not_found(msh, i);
}

/* In the ft_check_access() function, if the command is a full path, it checks
whether the command exists and is executable. */
void	ft_check_access(t_main *msh)
{
	if (access(msh->full_path, F_OK) == 0)
	{
		if (access(msh->full_path, X_OK) == 0)
		{
			msh->cmd_valid = 1;
		}
		else
		{
			//dprintf(2, "PATH Permission denied\n");
			ft_print_cmd_msg_error(msh, 2);
			ft_free_all(msh, NULL, true);
			msh->code_status = 126;
			exit(msh->code_status);
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
		//dprintf(2, "PATH Command not found\n");
		msh->code_status = 127;
		exit(msh->code_status);
	}
}
