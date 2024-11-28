/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:39:29 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/28 14:12:47 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{	
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	delete_var(char *arg, t_env **head)
{
	t_env	*current;
	t_env	*previous;

	current = *head;
	previous = NULL;
	if (current == NULL)
		return (0);
	while (current)
	{
		if (arg && ft_strcmp(arg, current->key) == 0)
		{
			free(current->key);
			free(current->value);
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
		}
		previous = current;
		// printf("current : %p\n", previous);
		// printf("HEAD : %p\n", *head);
		// printf("NOW : %p\n", current);
		// printf("PREVIOUS : %p\n", previous);
		current = current->next;
	}
	free(current);
	return (0);
}


int	ft_unset(char **arg, t_env **env)
{
	int i;

	t_env *cpy = *env;
	i = 1;
	if (strncmp("unset", arg[0], 5) == 0 && !arg[i]){
		return (0);
	}
	// if (strncmp("unset", arg[0], 6) != 0)
	// {
	// 	printf("%s: command not found\n", arg[0]);
	// 	return (0);
	// }
	if (arg[0] && arg[i])
	{
		delete_var(arg[i], env);
		while (cpy)
		{
			printf("KEY : %s | VALUE : %s\n", cpy->key,cpy->value);
			// printf("HELLO\n");
			cpy = cpy->next;
		}
	}
	return (0);
}