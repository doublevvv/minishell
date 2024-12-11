/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:25:39 by evlim             #+#    #+#             */
/*   Updated: 2024/12/06 16:57:11 by evlim            ###   ########.fr       */
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
		ft_free_double_array(msh->cmd_array);
		ft_free_all(msh, NULL);
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
	ft_putstr_fd(msh->cmd_array[0], 2);
	if (msg == 1)
	{
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (msg == 2)
	{
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

/* The ft_check_path() function searches for the command in the paths of
the `PATH` environment and checks whether the command exists and is executable
and stores all the informations about the command in a linked list. */
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
				dprintf(2, "ICI\n");
				ft_print_cmd_msg_error(msh, 2);
				ft_free_all(msh, NULL);
				exit(126);
			}
		}
		free(msh->full_path);
		i++;
	}
	if (msh->paths[i] == NULL)
	{
		dprintf(2, "ICI BIS\n");
		ft_print_cmd_msg_error(msh, 1);
		dprintf(2, "\t\tje suis le pid : %d\n", getpid());
		ft_free_all(msh, NULL);
		exit(127);
	}
}

/* In the ft_check_access() function, if the command is a full path, it checks
whether the command exists and is executable, then stores all the informations
about the command in a linked list. If not, we search for the command
in the paths of the `PATH` environment variable. */
void	ft_check_access(t_main *msh)
{
	if (access(msh->full_path, F_OK) == 0)
	{
		//dprintf(2, "fullpath: %s\n", msh->full_path);
		if (access(msh->full_path, X_OK) == 0)
		{
			msh->cmd_valid = 1;
		}
		else
		{
			dprintf(2, "LA\n");
			ft_print_cmd_msg_error(msh, 2);
			ft_free_all(msh, NULL);
			exit(126);
		}
	}
	else
	{
		dprintf(2, "LA BIS\n");
		ft_print_cmd_msg_error(msh, 1);
		ft_free_all(msh, NULL);
		exit(127);
	}
}

/* The ft_search_for_slash() function checks whether the command contains
a `/` character. If a `/` is found, the command is given as a full path
(relative/absolute path). */
bool	ft_search_for_slash(t_main *msh)
{
	int		i;
	t_lst	*tmp;
	t_lst	*tmp_arg;

	i = 0;
	tmp = msh->head_command;
	while (tmp != NULL)
	{
		tmp_arg = tmp->u_data.cmd_args;
		while (tmp_arg != NULL)
		{
			//dprintf(2, "u_data->word: %s\n", tmp_arg->u_data.word);
			while (tmp_arg->u_data.word[i] != '\0')
			{
				if (ft_strchr(&tmp_arg->u_data.word[i], '/') == 1)
				{
					msh->full_path = tmp_arg->u_data.word;
					//dprintf(2, "msh->full_path = %s\n", msh->full_path);
					return (true);
				}
				i++;
			}
			tmp_arg = tmp_arg->next;
		}
		tmp = tmp->next;
	}
	return (false);
}
