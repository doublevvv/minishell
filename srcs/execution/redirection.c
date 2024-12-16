/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:34:07 by evlim             #+#    #+#             */
/*   Updated: 2024/12/16 15:18:07 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_open_file_error(t_main *msh, int fd_infile, int fd_outfile)
{
	if (fd_outfile == -1)
	{
		if (fd_infile != -1)
		{
			close(fd_infile);
		}
	}
	ft_free_all(msh, "Error ", true);
}

void	ft_handle_redir_in(t_main *msh, char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_open_file_error(msh, 0, 0);
	}
}

void	ft_handle_redir_out(t_main *msh, char *filename, int *fd)
{
	*fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd == -1)
	{
		ft_open_file_error(msh, 0, -1);
	}
}

void	ft_handle_redir_append(t_main *msh, char *filename, int *fd)
{
	*fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd == -1)
	{
		ft_open_file_error(msh, 0, -1);
	}
}

/* The ft_open_redir() function handles input and output redirection.
Depending on the type of the redirection (e.g., input, output or heredoc),
it opens the appropriate files and updates the corresponding file descriptors
(fd_infile or fd_outfile). */
void	ft_open_redir(t_main *msh, t_lst *cmd_args)
{
	int	fd_infile;
	int	fd_outfile;

	fd_infile = -1;
	fd_outfile = -1;
	if (cmd_args->token_type == REDIRECTION_IN)
	{
		ft_handle_redir_in(msh, cmd_args->u_data.word, &fd_infile);
	}
	else if (cmd_args->token_type == REDIRECTION_OUT)
	{
		ft_handle_redir_out(msh, cmd_args->u_data.word, &fd_outfile);
	}
	else if (cmd_args->token_type == REDIRECTION_HEREDOC)
	{
		fd_infile = cmd_args->u_data.fd;
	}
	else if (cmd_args->token_type == REDIRECTION_APPEND)
	{
		ft_handle_redir_append(msh, cmd_args->u_data.word, &fd_outfile);
	}
	ft_dup_redirections(msh, fd_infile, fd_outfile);
	ft_close_redirections(fd_infile, fd_outfile);
}
