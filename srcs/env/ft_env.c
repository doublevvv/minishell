/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:22:11 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/19 09:04:35 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	copy_var(char *dest, char *src, size_t size)
{
	size_t	j;

	j = 0;
	while (j < size)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
}

int	init_env_val(size_t nbr2, size_t nbr3, char **key, char **value)
{
	(void)nbr2;
	(void)nbr3;
	*key = malloc(nbr3 + 1);
	if (!*key)
	{
		return (0);
	}
	*value = malloc(nbr2 + 1);
	if (!value)
	{
		free(*key);
		return (0);
	}
	return (1);
}

int	init_nbrs(size_t *nbr, size_t *nbr2, char *environ, char **tmp)
{
	*nbr = ft_strlen(environ);
	*tmp = ft_strchr_char(environ, '=');
	*nbr2 = ft_strlen(*tmp + 1) + 1;
	return (*nbr - *nbr2);
}

t_env	*get_env(char **environ, size_t nbr, size_t nbr2, size_t nbr3)
{
	int		i;
	t_env	*list;
	t_env	*new;
	t_chars	vars;

	i = -1;
	list = NULL;
	while (environ[++i])
	{
		nbr3 = init_nbrs(&nbr, &nbr2, environ[i], &vars.tmp);
		if (!init_env_val(nbr2, nbr3, &vars.key, &vars.value))
			ft_error_new(NULL, NULL, &list);
		vars.key[nbr3] = 0;
		copy_var(vars.key, environ[i], nbr3);
		copy_var(vars.value, vars.tmp + 1, nbr2);
		new = ft_lstnew_env(vars.key, vars.value);
		if (!new)
			ft_error_new(&vars.value, &vars.key, &list);
		ft_lstadd_back_env(&list, new);
	}
	if (ft_update_pwd(&list) == 0)
		ft_error_new(&vars.value, &vars.key, &list);
	return (list);
}
