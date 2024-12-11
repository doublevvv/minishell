/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:39:29 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/11 13:36:59 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	delete_var(char *arg, t_env *head)
{
	t_env	*current;
	t_env	*previous;

	current = head;
	previous = NULL;
	if (!arg)
		return (0);
	if (current == NULL)
		return (0);
	while (current)
	{
		// printf("cocuou unset\n");
		if (ft_strcmp(arg, current->key) == 0)
		{
			free(current->key);
			free(current->value);
			if (previous == NULL)
				head = current->next;
			else
				previous->next = current->next;
			free(current);
			break;
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
	if (ft_strncmp("unset", msh->cmd_array[0], 5) == 0 && !msh->cmd_array[i]) 
		return (0);
	if (ft_strncmp("unset", msh->cmd_array[0], 6) != 0)
	{
		printf("%s: command not found\n", msh->cmd_array[0]);
		return (0);
	}
	while (msh->cmd_array[i])
	{
		if (msh->cmd_array[0] && msh->cmd_array[i]) 
		{
			delete_var(msh->cmd_array[i], env);
			// while (cpy)
			// {
			// 	printf("KEY : %s | VALUE : %s\n", cpy->key,cpy->value);
			// 	// printf("HELLO\n");
			// 	cpy = cpy->next;
			// }
		}
		i++;
	}
	return (0);
}
