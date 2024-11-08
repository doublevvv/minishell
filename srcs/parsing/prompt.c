/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/07 14:50:31 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char	display_prompt(t_main *msh)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("les loutres > ");
// 		if (!line)
// 		{
// 			exit (1);
// 		}
// 		add_history(line);
// 	}
// 	msh->cmd = &line;
// 	int i = 0;
// 	while (msh->cmd[i])
// 	{
// 		printf("==%s\n", msh->cmd[i]);
// 		i++;
// 	}
// 	ft_display_lst(msh);
// }

char	display_prompt(t_main *msh)
{
	char	*line;

	while (1)
	{
		line = readline("les loutres > ");
		if (!line)
		{
			exit (1);
		}
		add_history(line);
		msh->tmp = ft_split(line, ' ');
		int i = 0;
		while (msh->tmp[i] != NULL)
		{
			printf("CMD : %s\n", msh->tmp[i]);
			i++;
		}
		ft_exit(msh->tmp);
		printf("------------------------\n");
	}

}