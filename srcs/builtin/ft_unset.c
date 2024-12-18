/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:39:29 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 08:55:59 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	delete_var(char *arg, t_env *head)
{
	t_env	*current;
	t_env	*previous;

	current = head;
	previous = NULL;
	if (!arg || current == NULL)
		return (0);
	while (current)
	{
		if (ft_strcmp(arg, current->key) == 0)
		{
			free(current->key);
			free(current->value);
			if (previous == NULL)
				head = current->next;
			else
				previous->next = current->next;
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_main *msh, t_env *env)
{
	int	i;

	i = 1;
	while (msh->cmd_array[i])
	{
		if (msh->cmd_array[0] && msh->cmd_array[i])
			delete_var(msh->cmd_array[i], env);
		i++;
	}
	return (0);
}
