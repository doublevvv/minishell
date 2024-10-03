/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:37 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/01 13:16:40 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
	(void)ac;
	t_main	msh;
	
	display_prompt(av[0]);
	manage_command(&msh, av[1]);
	printcmd(&msh);
	
}