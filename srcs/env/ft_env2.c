/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:35:33 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/19 09:07:54 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

int	ft_update_pwd(t_env **list)
{
	t_env	*new;
	t_env	*tmp_list;
	char	*name;

	tmp_list = *list;
	while (tmp_list)
	{
		if (ft_strcmp("PWD", tmp_list->key) == 0)
		{
			free(tmp_list->value);
			tmp_list->value = getcwd(NULL, 0);
			return (1);
		}
		tmp_list = tmp_list->next;
	}
	name = ft_strdup("PWD");
	if (!name)
		return (0);
	new = ft_lstnew_env(name, getcwd(NULL, 0));
	if (!new)
		return (free(name), 0);
	ft_lstadd_back_env((list), new);
	return (1);
}

void	ft_error_new(char **value, char **key, t_env **env)
{
	ft_print_error_message(ALLOCATION_FAILED, 0);
	if (*key)
		free(*key);
	if (*value)
		free(*value);
	if (*env)
	{
		lst_env_clear(env);
	}
	exit(EXIT_FAILURE);
}

void	ft_error_value(char **key)
{
	ft_print_error_message(ALLOCATION_FAILED, 0);
	if (*key)
		free(*key);
	exit(EXIT_FAILURE);
}
