/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:54:35 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/19 08:49:35 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strchr_char(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&str[i]);
	else
		return (NULL);
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	lst_env_clear(t_env **lst_env)
{
	t_env	*tmp;
	t_env	*current;

	current = *lst_env;
	while (current != NULL)
	{
		if (current->key)
		{
			free(current->key);
		}
		if (current->value)
		{
			free(current->value);
		}
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*lst_env = NULL;
}

void	ft_env(t_main *msh, t_env *environ)
{
	t_env	*cpy;

	cpy = environ;
	printf("ENV LIST\n");
	while (cpy != NULL)
	{
		if (printf("%s=%s\n", cpy->key, cpy->value) < 0)
		{
			ft_print_error_message(ALLOCATION_FAILED, 0);
			ft_free_all(msh, NULL, true);
		}
		cpy = cpy->next;
	}
	printf("----------------------------------\n");
}
