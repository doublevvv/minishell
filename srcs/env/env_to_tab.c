/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:26:02 by evlim             #+#    #+#             */
/*   Updated: 2024/12/18 13:26:51 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_join_key_to_value(t_main *msh, t_env *lst_env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(lst_env->key, "=");
	if (!tmp) //PB
	{
		ft_putstr_fd("Failed to join\n", 2);
		ft_free_all(msh, NULL, true);
	}
	result = ft_strjoin(tmp, lst_env->value);
	free(tmp);
	if (!result) //PB
	{
		ft_putstr_fd("Failed to join\n", 2);
		ft_free_all(msh, NULL, true);
	}
	return (result);
}

/* The ft_convert_env_lst_to_array() function converts the env linked list
into an array. */
void	ft_convert_env_lst_to_array(t_main *msh)
{
	int		nb_env_variable;
	int		i;
	int		y;
	t_env	*current;

	nb_env_variable = ft_lstsize(msh->env);
	current = msh->env;
	i = 0;
	msh->envp = malloc((nb_env_variable + 1) * sizeof(char *));
	if (!msh->envp)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		ft_free_all(msh, NULL, true);
	}
	while (current != NULL)
	{
		msh->envp[i] = ft_join_key_to_value(msh, current);
		if (!msh->envp[i])
		{
			y = 0;
			while (i > 0)
			{
				free(msh->envp[y]);
				i--;
				y++;
			}
			ft_putstr_fd("Failed to join key to value\n", 2);
			ft_free_all(msh, NULL, true);
		}
		i++;
		current = current->next;
	}
	msh->envp[i] = NULL;
}
