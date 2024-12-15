/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:39:02 by evlim             #+#    #+#             */
/*   Updated: 2024/12/13 17:13:52 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execute_parent(t_main *msh)
{
	if (msh->prev_pipe != -1)
	{
		close(msh->prev_pipe);
	}
	msh->prev_pipe = msh->pipefd[0];
	if (msh->pipefd[1] != -1)
	{
		close(msh->pipefd[1]);
	}
}

/* The ft_parent_wait() function waits for all the child processes to finish.
It updates a status code based on how each child process terminates
(normal or abnormal termination).

WIFEXITED(status) returns true if the child terminated normally 
(via exit or returning from main).
WEXITSTATUS(status) returns the exit status of the child.

WIFSIGNALED(status) returns true if the child process was terminated by a signal.
WTERMSIG(status) returns the number of the signal that caused the child process 
to terminate. */
void	ft_parent_wait(t_main *msh)
{
	t_lst	*cmd;
	int		status;

	status = 0;
	cmd = msh->head_command;
	while (cmd != NULL)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
		{
			msh->code_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			msh->code_status = WTERMSIG(status);
			msh->code_status += 128;
		}
		cmd = cmd->next;
	}
}

void	ft_final_execution(t_main *msh)
{
	if (msh->in_pipeline == 1)
	{
		ft_close_pipes_child(msh);
		ft_parent_wait(msh);

	}
	ft_free_all(msh, NULL, false);
}
