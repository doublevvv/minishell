/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:22:11 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/18 17:26:36 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (environ[++i])
	{
		nbr = ft_strlen(environ[i]);
		//printf("%ld\n", nbr);
		tmp = ft_strchr(environ[i], '=');
		nbr2 = ft_strlen(tmp + 1);
		//printf("%ld\n", nbr2);
		nbr3 = nbr - nbr2 - 1;
		//printf("%ld\n", nbr3);
		key = malloc(nbr3 + 1);
		strncpy(key, environ[i], nbr3);
		value = malloc(nbr2);
		if (!value)
			free(key);
		strncpy(value, tmp + 1, nbr2);
		// printf("%s\n", value + 1);
		//printf("%s\n", list->value);
		new = ft_lstnew_env(key, value);
		// if (!new);
			//PROTEGER (KEY?VALUE?LIST)
		ft_lstadd_back_env(&list, new);
		//ft_display_lst_env(env);
	
	}
	return (list);
}
