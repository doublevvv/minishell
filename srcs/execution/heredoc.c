/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:49:24 by evlim             #+#    #+#             */
/*   Updated: 2024/12/16 09:49:51 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* The ft_generate_random_filename() function creates a random filename for
the here_doc. */
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
	msh->heredoc_filename = ft_strjoin(path, str);
	if (!msh->heredoc_filename)
	{
		ft_putstr_fd("Failed to join to create heredoc file name\n", 2);
		ft_free_all(msh, NULL, true);
	}
}

/* The ft_read_input_heredoc() function reads from the standard input and
stores each line except the limiter in a temporary file.
This temporary file is taken as the infile of the program.*/
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
		if (ft_strcmp(cmd, line) == 0)
		{
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
