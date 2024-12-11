/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:26:02 by evlim             #+#    #+#             */
/*   Updated: 2024/12/11 13:48:26 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_join_key_to_value(t_env *lst_env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(lst_env->key, "=");
	if (!tmp)
	{
		ft_putstr_fd("Failed to join\n", 2);
		return (NULL); //+ free
	}
	result = ft_strjoin(tmp, lst_env->value);
	free(tmp);
	if (!result)
	{
		ft_putstr_fd("Failed to join\n", 2);
		return (NULL); //+ free
	}
	return (result);
}

void	ft_convert_lst_to_tab(t_main *msh)
{
	int		nb_env_variable;
	int		i;
	int		y;
	t_env	*current;

	nb_env_variable = ft_lstsize(msh->env);
	dprintf(2, "env_size = %d\n", nb_env_variable);
	i = 0;
	current = msh->env;
	msh->envp = malloc((nb_env_variable + 1) * sizeof(char *));
	if (!msh->envp)
	{
		;
		//free
	}
	while (current != NULL)
	{
		msh->envp[i] = ft_join_key_to_value(current);
		if (!msh->envp[i])
		{
			y = 0;
			while (i > 0)
			{
				free(msh->envp[y]);
				i--;
				y++;
			}
			ft_putstr_fd("Failed to join\n", 2);
			//free all
		}
		i++;
		current = current->next;
	}
	msh->envp[i] = NULL;
	//A SUPPRIMER
	i = 0;
	dprintf(2, "ENV TAB\n");
	while (msh->envp[i] != NULL)
	{
		dprintf(2, "msh->envp[%d] = %s\n", i, msh->envp[i]);
		i++;
	}
}
