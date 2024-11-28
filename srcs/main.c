/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:37 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/28 13:07:02 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_data(t_main *msh)
{
	ft_memset(msh, 0, sizeof(t_main));
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_main	msh;
	
	//proteger l'env si env -i
	ft_init_data(&msh);
	msh.env = get_env(envp);
	//ft_display_lst_env(msh.env);
	// while (msh.env)
	// {
	// 	printf("key : %s, value : %s\n", msh.env->key, msh.env->value);
	// 	msh.env = msh.env->next;
	// }
	display_prompt(&msh, msh.env);
	return (0);
}
