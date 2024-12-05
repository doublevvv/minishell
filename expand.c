/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:32 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/05 18:05:27 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	comp_var(char *var_name, char *key, int var_size)
{
	int i;

	i = 0;
	while (key[i] && i < var_size && var_name[i] == key[i])
		i++;
	printf("%s\n", key);
	printf("VAR SIZE : %d\n", var_size);
	printf("I SIZE : %d\n", i);
	// write(1, var_name, var_size - 2);
	// write(1, "\n", 1);
	printf("%.8s\n", var_name);
	if (i == var_size && key[i] == 0){
		printf(" i = %d && varsize = %d\n", i, var_size);
		return (0);
	}
	return (1);
}

char *ft_expand(char *arg, t_env *env)
{
	int i;
	int	var_size;
	char *res;
	int	res_index;
	t_env *cpy;
	//char *expand_value;

	i = 0;
	var_size = 0;
	res_index = 0;
	res = malloc(25000 * (sizeof(char) + 1));
	res[res_index] = 0;
	if (arg[i] == '$' && arg[i + 1] != '\0')
	{
		i++;
		if (ft_isalpha(arg[i]))
		{
			var_size++;
			while (ft_isalnum(arg[i + var_size]) || arg[i + var_size] == '_'){
				var_size++;
				printf("%d\n", var_size);}
			printf(" i ==%d\n", i);
			cpy = env;
			while (cpy)
			{
				if (comp_var(arg + i, cpy->key, var_size) == 0)
				{
					ft_memcpy(res + res_index, cpy->value, ft_strlen(cpy->value));
					res_index += ft_strlen(cpy->value);
					res[res_index] = 0;
					break ;
				}
				cpy = cpy->next;
			}
			i += var_size;
		}
	}
	printf("EXPAND : %s\n", res);
	return (res);
}

//gerer sigles et double quotes
//corriger le malloc 2500