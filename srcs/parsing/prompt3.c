/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:24:38 by evlim             #+#    #+#             */
/*   Updated: 2024/12/19 09:30:52 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lst	*ft_pipe_case(t_main *msh, int token)
{
	t_lst	*current_command;

	current_command = NULL;
	if (ft_verify_lst(msh->head_command) == false)
	{
		ft_print_error_message(EMPTY_WORD, '|');
		return (NULL);
	}
	current_command = ft_lstnew(token, NULL, -1);
	if (!current_command)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		return (NULL);
	}
	ft_lstadd_back(msh, &msh->head_command, current_command);
	return (current_command);
}

bool	ft_handle_signal_heredoc(t_main *msh)
{
	if (g_signal_global != 0)
	{
		free(msh->heredoc_filename);
		if (dup2(msh->stdin_copy, STDIN_FILENO) == -1)
		{
			free(msh->cmd);
			ft_free_all(msh, "Signal heredoc failed to dup2 stdin\n", true);
		}
		msh->code_status = 130;
		write(1, "\n", 1);
		return (false);
	}
	return (true);
}

bool	heredoc_operations(t_main *msh, int *fd_infile)
{
	ft_generate_random_filename(msh);
	msh->file = open(msh->heredoc_filename, O_CREAT | O_WRONLY, 0644);
	if (msh->file == -1)
	{
		ft_open_file_error(msh, 0, 0);
		ft_free_all(msh, NULL, true);
	}
	ft_read_input_heredoc(msh->cmd, msh->file);
	if (ft_handle_signal_heredoc(msh) == false)
		return (false);
	close (msh->file);
	msh->file = -1;
	*fd_infile = open(msh->heredoc_filename, O_RDONLY);
	//if (*fd_infile == -1) // PB : ne rentre pas dans la condition GROS PROBLEME
	{
		ft_open_file_error(msh, 0, 0);
		ft_free_all(msh, NULL, true);
	}
	unlink(msh->heredoc_filename);
	free(msh->heredoc_filename);
	msh->heredoc_filename = NULL;
	return (true);
}

t_lst	*ft_heredoc_case(t_main *msh, int token)
{
	int		fd_infile;
	t_lst	*command;

	fd_infile = -1;
	command = NULL;
	signal(SIGINT, here_doc_sig_handler);
	if (!heredoc_operations(msh, &fd_infile))
		return (NULL);
	command = ft_lstnew(token, msh->cmd, fd_infile);
	if (!command)
	{
		close(fd_infile);
		return (false);
	}
	free(msh->cmd);
	signal(SIGINT, SIG_IGN);
	return (command);
}

t_lst	*ft_command(t_main *msh, int token)
{
	t_lst	*command;

	if (token == REDIRECTION_HEREDOC)
		command = ft_heredoc_case(msh, token);
	else
		command = ft_lstnew(token, msh->cmd, -1);
	return (command);
}

bool	ft_display_error(t_main *msh)
{
	ft_print_error_message(ALLOCATION_FAILED, 0);
	free(msh->cmd);
	return (false);
}
