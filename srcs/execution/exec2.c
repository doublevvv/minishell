/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:39:02 by evlim             #+#    #+#             */
/*   Updated: 2024/12/16 10:52:51 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_redirect_pipes(t_main *msh, int old_fd, int new_fd)
{
	if (old_fd > -1 && dup2(old_fd, new_fd) == -1)
	{
		ft_free_all(msh, "dup2 failed", true);
	}
}

/* The dup_pipes() function manages file descriptors for input and output 
redirection depending on the command's position in the pipeline. */
void	ft_dup_pipes(t_main *msh, int nb)
{
	if (nb == 0)
	{
		ft_redirect_pipes(msh, msh->pipefd[1], STDOUT_FILENO);
		close(msh->pipefd[1]);
		msh->prev_pipe = -1;
	}
	else if (nb == (msh->nb_cmd - 1))
	{
		close(msh->pipefd[1]);
		msh->pipefd[1] = -1;
		ft_redirect_pipes(msh, msh->prev_pipe, STDIN_FILENO);
		close(msh->prev_pipe);
		msh->prev_pipe = -1;
	}
	else
	{
		ft_redirect_pipes(msh, msh->prev_pipe, STDIN_FILENO);
		close(msh->prev_pipe);
		msh->prev_pipe = -1;
		ft_redirect_pipes(msh, msh->pipefd[1], STDOUT_FILENO);
		close(msh->pipefd[1]);
		msh->pipefd[1] = -1;
	}
}
