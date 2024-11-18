/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:22:11 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/18 12:42:36 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **environ)
{
	int i;
	char *tmp;
	char *cpy;
	char *cpy2;
	t_env	*list;
	t_main	*env;
	size_t nbr;
	size_t nbr2;
	size_t nbr3;

	i = -1;
	env = NULL;
	list = malloc(sizeof(t_env));
	while (environ[++i])
	{
		nbr = ft_strlen(environ[i]);
		//printf("%ld\n", nbr);
		tmp = ft_strchr(environ[i], '=');
		nbr2 = ft_strlen(tmp);
		//printf("%ld\n", nbr2);
		nbr3 = nbr - nbr2;
		//printf("%ld\n", nbr3);
		cpy = malloc(nbr3 + 1);
		strncpy(cpy, environ[i], nbr3);
		list->key = cpy;
		cpy2 = malloc(nbr2 + 1);
		strncpy(cpy2, tmp, nbr2);
		// printf("%s\n", cpy2 + 1);
		list->value = cpy2 + 1;
		printf("%s\n", list->value);
		ft_add_cmd_to_lst(env);
		ft_display_lst_env(env);
	
	}
	return (environ);
	
}
