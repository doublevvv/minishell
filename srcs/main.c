/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:37 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/15 16:25:49 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_data(t_main *msh)
{
	ft_memset(msh, 0, sizeof(t_main));
	msh->double_quote = true;
	msh->simple_quote = true;
}

int	main(void)
{
	t_main	msh;

	ft_init_data(&msh);
	display_prompt(&msh);
	return (0);
}
