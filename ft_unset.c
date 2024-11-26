/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:39:29 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/26 16:22:00 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	renew_linked_list(char *arg, t_env **head)
{
	t_env	*current;
	t_env	*previous;

	current = *head;
	while (current)
	{
		if (ft_strcmp(arg, current->key) == 0)
		{
			free(current->key);
			free(current->value);
		}
		previous = 
	}
}
int	unset(char **arg, t_env **env)
{
	int i;

	i = 1;
	if (arg[0] && !arg[i])
		return (0);
	else if (arg[0] && arg[i])
	{
		
	}
}