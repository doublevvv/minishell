/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:41:13 by evlim             #+#    #+#             */
/*   Updated: 2024/12/16 18:24:12 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execute_command(t_main *msh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_convert_env_lst_to_array(msh);
	ft_search_env_path(msh);
	if (ft_get_paths(msh) == false)
	{
		ft_free_all(msh, NULL, true);
	}
	if (ft_strchr(msh->cmd_array[0], '/') == 1)
	{
		msh->full_path = msh->cmd_array[0];
		ft_check_access(msh);
	}
	else
	{
		ft_check_path(msh);
	}
	if (execve(msh->full_path, msh->cmd_array, msh->envp) == -1)
	{
		ft_free_all(msh, "execve failed", true);
	}
}

/* The ft_not_in_pipeline() function manages the execution of a single builtin
or command. Based on this, it executes the corresponding function.
If it is a command, it creates a new process using the fork function. */
void	ft_not_in_pipeline(t_main *msh, t_lst *cmd, int builtin)
{
	if (builtin != -1)
	{
		ft_execute_builtin(msh, builtin);
	}
	else
	{
		msh->in_pipeline = 1;
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			close(msh->stdin_copy);
			close(msh->stdout_copy);
			ft_execute_command(msh);
		}
	}
}

/* The ft_in_pipeline() function manages the execution of commands within a
pipeline. It creates a new process using the fork function and based on
whether the argument is a builtin or a command, it executes the corresponding
function. */
void	ft_in_pipeline(t_main *msh, t_lst *cmd, int builtin)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (builtin != -1)
		{
			ft_execute_builtin(msh, builtin);
			close(msh->stdin_copy);
			close(msh->stdout_copy);
			ft_close_pipes(msh);
			ft_free_all(msh, NULL, true);
		}
		else
		{
			close(msh->stdin_copy);
			close(msh->stdout_copy);
			ft_close_pipes(msh);
			ft_execute_command(msh);
		}
	}
}

void	ft_handle_exec( t_main *msh, t_lst *cmd, int nb)
{
	t_lst	*cmd_arg;
	int		builtin;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cmd_arg = cmd->u_data.cmd_args;
	if (msh->cmd_array != NULL)
	{
		free(msh->cmd_array);
	}
	ft_create_cmd_array(msh, cmd_arg);
	builtin = 0;
	if (msh->nb_cmd > 1)
	{
		ft_dup_pipes(msh, nb);
	}
	ft_handle_redirections(msh, cmd_arg);
	if (msh->cmd_array[0] == NULL)
		return ;
	builtin = ft_is_builtin(msh->cmd_array[0]);
	if (msh->in_pipeline == 0)
		ft_not_in_pipeline(msh, cmd, builtin);
	else
		ft_in_pipeline(msh, cmd, builtin);
}

void	ft_count_cmds(t_main *msh, t_lst *lst)
{
	msh->nb_cmd = 0;
	while (lst != NULL)
	{
		msh->nb_cmd++;
		lst = lst->next;
	}
}

void	ft_exec(t_main *msh)
{
	t_lst	*cmd;
	int		i;

	cmd = msh->head_command;
	i = 0;
	ft_count_cmds(msh, cmd);
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			if (pipe(msh->pipefd) == -1)
			{
				ft_free_all(msh, "pipe failed", true);
			}
			msh->in_pipeline = 1;
		}
		ft_handle_exec(msh, cmd, i);
		ft_execute_parent(msh);
		i++;
		cmd = cmd->next;
		if (dup2(msh->stdout_copy, STDIN_FILENO) == -1 \
			|| dup2(msh->stdout_copy, STDOUT_FILENO) == -1)
			ft_free_all(msh, "Failed to restore stdin/stdout", true);
	}
	ft_final_execution(msh);
}
