/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:34:07 by evlim             #+#    #+#             */
/*   Updated: 2024/12/16 10:57:57 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_open_file_error(t_main *msh, int fd_infile, int fd_outfile)
{
	if (fd_outfile == -1)
	{
		if (fd_infile != -1)
		{
			//dprintf(2, "error fd_infile\n");
			close(fd_infile);
		}
		//dprintf(2, "error fd_outfile\n");
	}
	ft_free_all(msh, "Error ", true);
}

void	ft_dup_redirections(t_main *msh, int fd_infile, int fd_outfile)
{
	if (fd_infile > -1 && dup2(fd_infile, STDIN_FILENO) == -1)
	{
		ft_free_all(msh, "1 => dup2 failed", true);
	}
	if (fd_outfile > -1 && dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		ft_free_all(msh, "2 => dup2 failed", true);
	}
}

void	ft_close_redirections(int fd_infile, int fd_outfile)
{
	if (fd_infile != -1)
	{
		dprintf(2, "fd_infile closed\n");
		close(fd_infile);
		fd_infile = -1;
	}
	if (fd_outfile != -1)
	{
		dprintf(2, "fd_outfile closed\n");
		close(fd_outfile);
		fd_outfile = -1;
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
		fd_infile = open(cmd_args->u_data.word, O_RDONLY);
		if (fd_infile == -1)
		{
			ft_open_file_error(msh, 0, 0);
		}
	}
	else if (cmd_args->token_type == REDIRECTION_OUT)
	{
		fd_outfile = open(cmd_args->u_data.word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_outfile == -1)
		{
			ft_open_file_error(msh, 0, -1);
		}
	}
	else if (cmd_args->token_type == REDIRECTION_HEREDOC)
	{
		fd_infile = cmd_args->u_data.fd;
	}
	else if (cmd_args->token_type == REDIRECTION_APPEND)
	{
		fd_outfile = open(cmd_args->u_data.word, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd_outfile == -1)
		{
			ft_open_file_error(msh, 0, -1);
		}
	}
	ft_dup_redirections(msh, fd_infile, fd_outfile);
	ft_close_redirections(fd_infile, fd_outfile);
}

/* The ft_handle_redirections() function:
- If the token is not a word, it calls ft_open_redir() to handle redirections.
- Otherwise, it adds the token to the command array, which stores the command's
name and its arguments.*/
void	ft_handle_redirections(t_main *msh, t_lst *cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args != NULL)
	{
		if (cmd_args->token_type != WORD)
		{
			ft_open_redir(msh, cmd_args);
		}
		else
		{
			if (cmd_args->u_data.word != NULL)
			{
				msh->cmd_array[i] = cmd_args->u_data.word;
				i++;
			}
		}
		cmd_args = cmd_args->next;
	}
	msh->cmd_array[i] = NULL;
}
