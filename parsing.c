/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:11:22 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/01 14:24:54 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*manage_command(t_main *msh, char *argv)
{
	int i = 0;
	
	while (argv)
	{
		if (argv[i + 1] == ' ')
			msh->cmd = ft_split(argv, ' ');
		else if (argv[i + 1] == '>')
			msh->cmd = ft_split(argv, '>');
		else if (argv[i + 1] == '<')
			msh->cmd = ft_split(argv, '<');
		else if (argv[i + 1] == '|')
			msh->cmd = ft_split(argv, '|');
		i++;
	}
	ft_lstadd_back(&msh->linked_list, ft_lstnew(msh->cmd));
	return (msh->cmd[i]);
}

void	printcmd(t_main *msh)
{
	int i = 0;
	while (msh->cmd[i] != NULL)
	{
		printf("%s\n", msh->cmd[i]);
		i++;
	}
}
