/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:24 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 18:45:23 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	case_sensivity(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!((ft_isalpha(arg[0]) || arg[0] == '_') && (ft_isdigit(arg[i])
					|| ft_isalpha(arg[i]) || arg[i] == '_')))
		{
			ft_printf(2, "les loutres: export: %s: not a valid identifier\n",
				arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	change_value(char *key, char *value, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (comp_var(key, tmp->key, ft_strlen(key)) == 0)
		{
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	error_value(char *value, char *key, t_main *msh)
{
	if (!value)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		free(key);
		ft_free_all(msh, NULL, true);
	}
}
