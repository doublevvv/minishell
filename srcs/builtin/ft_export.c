/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:24 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/13 08:58:41 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_ascii_order(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

static void	copy_var(char *src, char *dest, size_t size)
{
	size_t	j;

	j = -1;
	while (++j < size)
		src[j] = dest[j];
	src[j] = 0;
}

int	add_var(t_main *msh, char *arg, t_env *env)
{
	char	*tmp;
	char	*key;
	char	*value;
	t_env	*new;
	size_t	nbr;
	size_t	nbr2;

	nbr = ft_strlen(arg);
	tmp = ft_strchr_char(arg, '=');
	nbr2 = ft_strlen(tmp + 1) + 1;
	key = ft_calloc(nbr - nbr2 + 1, sizeof(char));
	copy_var(key, arg, nbr - nbr2);
	value = malloc(nbr2 + 1);
	if (!value)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		free(key);
		ft_free_all(msh, NULL, true);
	}
	copy_var(value, tmp + 1, nbr2);
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
		// gerer underscore ?
		{
			printf("les loutres: export: %s: not a valid identifier\n", arg);
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
		if (msh->cmd_array[0] && msh->cmd_array[i]) // add var to env
		{
			add_var(msh, msh->cmd_array[i], env);
			while (cpy)
			{
				printf("KEY : %s | VALUE : %s\n", cpy->key, cpy->value);
				cpy = cpy->next;
			}
		}
		i++;
	}
	return (0);
}
