/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:37 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/16 09:32:44 by evlim            ###   ########.fr       */
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
*/