/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:16:58 by evlim             #+#    #+#             */
/*   Updated: 2024/12/17 09:13:20 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_pipes(t_main *msh)
{
	if (msh->pipefd[1] > -1)
	{
		close (msh->pipefd[1]);
		msh->pipefd[1] = -1;
	}
	if (msh->pipefd[0] > -1)
	{
		close (msh->pipefd[0]);
		msh->pipefd[0] = -1;
	}
	if (msh->prev_pipe > -1)
	{
		close(msh->prev_pipe);
		msh->prev_pipe = -1;
	}
}

void	ft_close_pipes_child(t_main *msh)
{
	t_lst	*cmd;

	cmd = msh->head_command;
	while (cmd != NULL)
	{
		if (msh->prev_pipe != -1)
		{
			close(msh->prev_pipe);
			msh->prev_pipe = -1;
		}
		if (msh->pipefd[1] != -1)
		{
			close(msh->pipefd[1]);
			msh->pipefd[1] = -1;
		}
		cmd = cmd->next;
	}
}

void	ft_close_pipes_parent(t_main *msh)
{
	if (msh->prev_pipe != -1)
	{
		close(msh->prev_pipe);
			msh->prev_pipe = -1;
	}
	msh->prev_pipe = msh->pipefd[0];
	if (msh->pipefd[1] != -1)
	{
		close(msh->pipefd[1]);
		msh->pipefd[1] = -1;
	}
}