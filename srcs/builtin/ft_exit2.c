/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:10:04 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 11:39:15 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	is_overflow(t_main *msh)
{
    int exit_code;
    
    if ((ft_overflow(msh->cmd_array[1]) == true)) // rename func
    {
        exit_code = 2;
        ft_printf(2, "les loutres: exit: %s: numeric argument required\n", msh->cmd_array[1]);
        ft_free_all(msh, NULL, false);
        exit(2);
    }
}
