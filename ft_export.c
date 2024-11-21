/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:24 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/20 15:38:58 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char **arg, char **env)
{
	if (ft_strncmp("export", arg[0], 7) != 0)
	{
		printf("%s: command not found\n", arg[0]);
		return (0);
	}
	if (arg[0] && ft_strchr(arg[1], "="))
	{
			
	}
}