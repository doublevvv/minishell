/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:22:11 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/02 10:51:27 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void copy_var(char *src, char *dest, size_t size)
{
	size_t j;
	for (j = 0; j < size; j++)
		src[j] = dest[j];
	src[j] = 0;
}

t_env	*get_env(char **environ)
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
