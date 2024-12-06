/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:32 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/06 16:18:21 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};

int	comp_var(char *var_name, char *key, int var_size)
{
	int i;

	i = 0;
	while (key[i] && i < var_size && var_name[i] == key[i])
		i++;
	// printf("%s\n", key);
	// printf("VAR SIZE : %d\n", var_size);
	// printf("I SIZE : %d\n", i);
	// printf("%.8s\n", var_name);
	if (i == var_size && key[i] == 0){
		printf(" i = %d && varsize = %d\n", i, var_size);
		return (0);
	}
	return (1);
}

void	check_quotes(char quote, int *index, int *quote_state)
{
	if (quote == '"' && *quote_state == NO_QUOTE)
	{
		*index = *index + 1;
		*quote_state = DOUBLE_QUOTE;
	}
	else if (quote == '"' && *quote_state == DOUBLE_QUOTE)
	{
		*index = *index + 1;
		*quote_state = NO_QUOTE;
	}
	else if (quote == '\'' && *quote_state == NO_QUOTE)
	{
		*index = *index + 1;
		*quote_state = SINGLE_QUOTE;
	}
	else if (quote == '\'' && *quote_state == SINGLE_QUOTE)
	{
		*index = *index + 1;
		*quote_state = NO_QUOTE;
	}	
}

char *ft_expand(char *arg, t_env *env)
{
	int i;
	int	var_size;
	char *res;
	int	res_index;
	t_env *cpy;
	int	quote_state;
	char *expand_value;

	i = 0;
	quote_state = NO_QUOTE;
	var_size = 0;
	res_index = 0;
	expand_value = NULL;
	res = malloc(25000 * (sizeof(char) + 1));
	if (!res)
		return (NULL);
	res[res_index] = 0;
	while (arg[i])
	{	
		if (arg[i] == '\'' || '"')
			check_quotes(arg[i], &i, &quote_state);
		if (arg[i] == '$' && arg[i + 1] != '\0' && quote_state != SINGLE_QUOTE) //gerer le else si ce n'est pas un dollar, cpier juste caractere dasn variable
		{
			i++;
			printf("I = %d\n", i);
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
					// printf("HRE\n");
					if (comp_var(arg + i, cpy->key, var_size) == 0)
					{
						printf("HERE\n");
						ft_memcpy(res + res_index, cpy->value, ft_strlen(cpy->value));
						res_index += ft_strlen(cpy->value);
						res[res_index] = 0;
						break ;
					}
					cpy = cpy->next;
				}
				i += var_size;
			}
			printf("EXPAND : %s\n", res);
			return (res);// ne pas retourner res en plein milieu, boucle cassee 
		}
		else
			expand_value = ft_strdup(arg);//expand_value[expand_index] = arg[i]; i++; expand_index++;
	}
	return (expand_value);
}

//corriger le malloc 2500
//gerer sigles et double quotes