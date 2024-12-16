/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:05:14 by evlim             #+#    #+#             */
/*   Updated: 2024/12/16 15:17:41 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_dup_redirections(t_main *msh, int fd_infile, int fd_outfile)
{
	if (fd_infile > -1 && dup2(fd_infile, STDIN_FILENO) == -1)
	{
		ft_free_all(msh, "dup2 failed", true);
	}
	if (fd_outfile > -1 && dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		ft_free_all(msh, "dup2 failed", true);
	}
}

void	ft_close_redirections(int fd_infile, int fd_outfile)
{
	if (fd_infile != -1)
	{
		close(fd_infile);
		fd_infile = -1;
	}
	if (fd_outfile != -1)
	{
		close(fd_outfile);
		fd_outfile = -1;
	}
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
