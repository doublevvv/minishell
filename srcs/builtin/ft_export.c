/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:24 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 09:05:51 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	copy_var(char *src, char *dest, size_t size)
{
	size_t	j;

	j = -1;
	while (++j < size)
		src[j] = dest[j];
	src[j] = 0;
}

static void	print_ascii_order(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

int	change_value(char *key, char *value, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (comp_var(key, tmp->key, ft_strlen(key)) == 0)
		{
			// free(tmp->value);
			// ft_memcpy(tmp->value, value, ft_strlen(value));
			tmp->value = value;
			// env->value = tmp->value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_env	*add_to_linkedlist(t_main *msh, char *key, char *value, t_env *new)
{
	new = ft_lstnew_env(key, value);
	if (!new)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		free(key);
		free(value);
		ft_free_all(msh, NULL, true);
	}
	return (new);
}

int	add_var(t_main *msh, char *arg, t_env *env, size_t nbr, size_t nbr2)
{
	char	*tmp;
	char	*key;
	char	*value;
	t_env	*new;

	nbr = ft_strlen(arg);
	tmp = ft_strchr_char(arg, '=');
	nbr2 = ft_strlen(tmp + 1) + 1;
	key = ft_calloc(nbr - nbr2 + 1, sizeof(char));
	if (!key)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		ft_free_all(msh, NULL, true);
	}
	copy_var(key, arg, nbr - nbr2);
	value = malloc(nbr2 + 1);
	if (!value)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		free(key);
		ft_free_all(msh, NULL, true);
	}
	copy_var(value, tmp + 1, nbr2);
	if (change_value(key, value, env))
		return (1);
	new = ft_lstnew_env(key, value);
	if (!new)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		free(key);
		free(value);
		ft_free_all(msh, NULL, true);
	}
	ft_lstadd_back_env(&env, new);
	return (0);
}

int	case_sensivity(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!((ft_isalpha(arg[0]) || arg[0] == '_') && (ft_isdigit(arg[i])
					|| ft_isalpha(arg[i]) || arg[i] == '_')))
		{
			ft_printf(2, "les loutres: export: %s: not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_main *msh, t_env *env)
{
	int		i;
	t_env	*cpy;

	i = 1;
	cpy = env;
	if (ft_strncmp("export", msh->cmd_array[0], 7) != 0)
	{
		ft_print_cmd_msg_error(msh, 1);
		return (0);
	}
	if (msh->cmd_array[0] && !msh->cmd_array[i])
		print_ascii_order(cpy);
	while (msh->cmd_array[i])
	{
		if (case_sensivity(msh->cmd_array[i]))
		{
			i++;
			continue ;
		}
		if (msh->cmd_array[0] && msh->cmd_array[i])
			add_var(msh, msh->cmd_array[i], env, 0, 0);
		i++;
	}
	return (0);
}
