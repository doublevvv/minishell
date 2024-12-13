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

// The ft_parent_wait() waits for the children processes to finish.
/*
WIFEXITED(wstatus)
	returns true if the child terminated normally,
    that is, by calling exit(3) or _exit(2), or by
    returning from main().

WEXITSTATUS(wstatus)
	returns the exit status of  the  child.
	This consists of the least significant 8 bits of
	the status argument that the child specified
	in a call to exit(3) or _exit(2) or as the argument
	for a return statement in main().
	This macro should be employed only if WIFEXITED returned true.

WIFSIGNALED(wstatus)
    returns true if the child process  was  terminated by a signal.

WTERMSIG(wstatus)
    returns  the  number of the signal that caused
    the child process to  terminate.
	This macro should be employed only if WIFSIGNALED returned true.
*/

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

void	ft_parent_wait(t_main *msh)
{
	t_lst	*cmd;
	int		status;

	status = 0;
	cmd = msh->head_command;
	while (cmd != NULL)
	{
		//dprintf(2, "cmd->pid = %d\n", cmd->pid);
		waitpid(cmd->pid, &status, 0);
		//dprintf(2, "word is %s\n", cmd->u_data.cmd_args->u_data.word);
		//dprintf(2, "On a attendu le pid %d\n", cmd->pid);
		if (WIFEXITED(status))
		{
			msh->code_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			msh->code_status = WTERMSIG(status);
			msh->code_status += 128; // cf wait
		}
		cmd = cmd->next;
	}
}

void	ft_final_execution(t_main *msh)
{
	//dprintf(2, "FINAL EXECUTION\n");
	if (msh->in_pipeline == 1)
	{
		ft_close_pipes_child(msh);
	}
	if (msh->in_pipeline == 1)
	{
		ft_parent_wait(msh);
	}
	ft_free_all(msh, NULL, false);
}
