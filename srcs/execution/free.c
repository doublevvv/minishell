/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:16:58 by evlim             #+#    #+#             */
/*   Updated: 2024/12/10 12:49:22 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_pipes(t_main *msh)
{
	if (msh->pipefd[0] != -1)
	{
		close (msh->pipefd[0]);
		//dprintf(2, "pipefd[0] closed\n");
		msh->pipefd[0] = -1;
	}
	if (msh->pipefd[1] != -1)
	{
		close (msh->pipefd[1]);
		//dprintf(2, "pipefd[1] closed\n");
		msh->pipefd[1] = -1;
	}
}

void	ft_close_pipes_child(t_main *msh)
{
	t_lst	*cmd;

	cmd = msh->head_command;
	while (cmd)
	{
		if (msh->prev_pipe != -1)
		{
			close(msh->prev_pipe);
			//dprintf(2, "pipefd[0] closed\n");
			msh->prev_pipe = -1;
		}
		if (msh->pipefd[1] != -1)
		{
			close(msh->pipefd[1]);
			//dprintf(2, "pipefd[1] closed\n");
			msh->pipefd[1] = -1;
		}
		cmd = cmd->next;
	}
}

// void	ft_close_all(t_main *msh)
// {
// 	int	i;

// 	i = 0;
// 	while (i < msh->nb_cmd - 1)
// 	{
// 		ft_close_pipes(msh);
// 		ft_close_fds(msh);
// 		i++;
// 	}
// }
