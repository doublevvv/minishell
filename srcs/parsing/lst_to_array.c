/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:41:51 by evlim             #+#    #+#             */
/*   Updated: 2024/12/06 09:18:37 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_create_cmd_array(t_main *msh, t_lst *tmp)
{
	msh->nb_cmd_array = 0;
	while (tmp != NULL)
	{
		if (tmp->token_type == WORD)
		{
			//dprintf(2, "IT'S A WORD\n");
			msh->nb_cmd_array++;
		}
		tmp = tmp->next;
	}
	//dprintf(2, "ICI nb cmd array = %d\n", msh->nb_cmd_array);
	msh->cmd_array = malloc((msh->nb_cmd_array + 1) * sizeof(char *));
	if (!msh->cmd_array)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		//exit (1);
	}
}

void	ft_display_cmd_array(t_main *msh)
{
	int	i;

	i = 0;
	dprintf(2, "Array of commands\n");
	while (msh->cmd_array[i] != NULL)
	{
		dprintf(2, "cmd %d, %s\n", i, msh->cmd_array[i]);
		i++;
	}
}
