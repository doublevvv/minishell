/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/04 13:24:26 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	display_prompt(t_main *msh, t_env *env)
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
		// int i = 0;
		// while (msh->tmp[i] != NULL)
		// {
		// 	printf("CMD : %s\n", msh->tmp[i]);
		// 	i++;
		// }
		printf("------------------------\n");
		// ft_exit(msh->tmp, &env);
		//ft_cd(msh->tmp, &env);
		//ft_echo(msh->tmp, &env);
		//ft_unset(msh->tmp, &env);
		ft_export(msh->tmp, &env);
		// ft_pwd(msh->tmp, &env);
	}

}