/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:34:07 by evlim             #+#    #+#             */
/*   Updated: 2024/12/12 13:40:18 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_open_file_error(t_main *msh, int fd_infile, int fd_outfile)
{
	if (fd_outfile == -1)
	{
		if (fd_infile != -1)
		{
			dprintf(2, "error fd_infile\n");
			close(fd_infile);
		}
		dprintf(2, "error fd_outfile\n");
	}
	ft_free_all(msh, "Error ", true);
}

void	ft_generate_random_filename(t_main *msh)
{
	unsigned char	*rand;
	int				i;
	char			str[9];
	char			*path;

	path = "/tmp/";
	rand = (unsigned char *)&msh;
	i = 0;
	while (i < 8)
	{
		str[i] = ((rand[i] % 26) + 'a');
		i++;
	}
	str[8] = '\0';
	msh->heredoc_filename = ft_strjoin(path, str); // a free
	if (msh->heredoc_filename == NULL)
	{
		ft_putstr_fd("Failed to join to create heredoc file name\n", 2);
		ft_free_all(msh, NULL, true);
	}
}

void	ft_read_input_heredoc(char *cmd, int file)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(file);
			break ;
		}
		dprintf(2, "delimiter = %s\n", cmd);
		dprintf(2, "line = %s\n", line);
		dprintf(2, "return strcmp = %d\n", ft_strcmp(cmd, line));
		if (ft_strcmp(cmd, line) == 0)
		{
			dprintf(2, "IDEM\n");
			free(line);
			close(file);
			break ;
		}
		else
		{
			ft_putstr_fd(line, file);
			write(file, "\n", 1);
		}
		free(line);
	}
}
void	ft_open_redir(t_main *msh, t_lst *cmd_args)
{
	int	fd_infile;
	int	fd_outfile;

	fd_infile = -1;
	fd_outfile = -1;
	if (cmd_args->token_type == REDIRECTION_IN)
	{
		dprintf(2, "REDIRECTION IN\n");
		fd_infile = open(cmd_args->u_data.word, O_RDONLY);
		//dprintf(2, "ICI fd_infile: %d\n", fd_infile);
		if (fd_infile == -1)
		{
			ft_open_file_error(msh, 0, 0);
			ft_free_all(msh, NULL, true);
		}
	}
	else if (cmd_args->token_type == REDIRECTION_OUT)
	{
		dprintf(2, "REDIRECTION OUT\n");
		fd_outfile = open(cmd_args->u_data.word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		//dprintf(2, "ICI fd_outfile: %d\n", fd_outfile);
		if (fd_outfile == -1)
		{
			ft_open_file_error(msh, 0, -1);
			ft_free_all(msh, NULL, true);
		}
	}
	else if (cmd_args->token_type == REDIRECTION_HEREDOC)
	{
		dprintf(2, "cmd_args %d\n", cmd_args->u_data.fd);
		fd_infile = cmd_args->u_data.fd;
		dprintf(2, "fd_infile %d\n", fd_infile);
	}
	else if (cmd_args->token_type == REDIRECTION_APPEND)
	{
		dprintf(2, "REDIRECTION APPEND\n");
		//dprintf(2, "cmd_args->u.data.word = %s\n", cmd_args->u_data.word);
		fd_outfile = open(cmd_args->u_data.word, O_CREAT | O_WRONLY | O_APPEND, 0644);
		//dprintf(2, "LA fd_outfile: %d\n", fd_outfile);
		if (fd_outfile == -1)
		{
			ft_open_file_error(msh, 0, -1);
			ft_free_all(msh, NULL, true);
		}
	}
	//dup de la redir function
	if (fd_infile > -1 && dup2(fd_infile, STDIN_FILENO) == -1)
	{
		ft_free_all(msh, "1 => dup2 failed", true);
	}
	if (fd_outfile > -1 && dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		ft_free_all(msh, "2 => dup2 failed", true);
	}
	//close function
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
