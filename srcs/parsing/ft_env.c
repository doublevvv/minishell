/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:22:11 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/11 13:58:19 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static void	copy_var(char *src, char *dest, size_t size)
{
	size_t	j;

	j = 0;
	while (j < size)
	{
		src[j] = dest[j];
		j++;
	}
	src[j] = 0;
}

void	*get_env(char **environ)
{
	int i;
	char *tmp;
	char *key;
	char *value;
	t_env	*list;
	t_env	*new;
	size_t nbr;
	size_t nbr2;
	size_t nbr3;

	i = -1;
	list = NULL;
	while (environ[++i])
	{
		nbr = ft_strlen(environ[i]);
		tmp = ft_strchr(environ[i], '=');
		nbr2 = ft_strlen(tmp + 1) + 1;
		nbr3 = nbr - nbr2;
		key = malloc(nbr3 + 1);
		// printf("environ[%d] ==%s, nbr == %zu , nbr 2 == %zu, nbr 3 == %zu\n", i, environ[i], nbr, nbr2, nbr3);
		// size_t j;
		// for (j = 0; j < nbr3; j++)
		// 	key[j] = environ[i][j];
		// key[j] = 0;
		//ft_strncpy(key, environ[i], nbr3);
		key[nbr3] = 0;//parcque e vraai ne met un \0 qu e si present dans les n octets le ft sans doute pas e soucis
		copy_var(key, environ[i], nbr3);
		value = malloc(nbr2 + 1);
		if (!value)
			free(key);
		//ft_strncpy(value, tmp + 1, nbr2);
		copy_var(value, tmp + 1, nbr2);
		// for (j = 0; j < nbr2; j++)
		// 	value[j] = environ[i][j];
		// value[j] = 0;
		new = ft_lstnew_env(key, value);
		// if (!new);
			//PROTEGER (KEY/VALUE/LIST)
		ft_lstadd_back_env(&list, new);
	}
	return (list);
}

// void	ft_display_lst_env(t_env *environ)
// {
// 	t_env	*cpy;

// 	cpy = environ;
// 	dprintf(2, "LISTE ENV\n");
// 	while (cpy != NULL)
// 	{
// 		printf(2, "KEY : %s\n", cpy->key);
// 		dprintf(2, " VALUE : %s\n", cpy->value);
// 		cpy = cpy->next;
// 	}
// 	printf("----------------------------------\n");
// }
