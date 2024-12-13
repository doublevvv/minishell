/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:37 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/13 15:13:11 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	msh;

	(void)argc;
	(void)argv;
	ft_init_data(&msh, envp);
	ft_msh_loop(&msh);
	return (msh.code_status);
}

/*
make re; valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=ignore ./minishell

void	ft_print_cmd_msg_error(t_main *msh, int msg)
{
	char buffer[2048];
	//strlcpy(buffer, msh->cmd);
	ft_putstr_fd(msh->cmd_array[0], 2);
	if (msg == 1)
	{
		//strcat(buffer, ": command not found\n");
	}
	else if (msg == 2)
	{
		//strcat(buffer, ": Permission denied\n");	
	}
	// ft_putstr(buffer, 2);
}
*/