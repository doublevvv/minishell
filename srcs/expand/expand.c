/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:32 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/17 10:12:39 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_size(t_size *line, char c)
{
	char	*tmp;

	if (line->capacity == 0 ||  line->line_size == line->capacity)
	{
		if (line->capacity != 0)
			line->capacity = line->capacity * 3;
		else
			line->capacity = 20;
		tmp = malloc(sizeof(char) * (line->capacity + 1));
		if (!tmp)//si ca echoue free la ligne actuielle
		{
			free(line->line);
			return (0);
		}
		if (line->line_size > 0)
		{
			ft_memcpy(tmp, line->line, ft_strlen(line->line));
			free(line->line);
		}
		line->line = tmp;
	}
	//printf("size == %d, capaciity == %d\n", line->line_size, line->capacity);
	line->line[line->line_size] = c;
	line->line_size++;
	line->line[line->line_size] = '\0';
	return (1);
}

int	add_size_to_str(t_size *line, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!add_size(line, str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	comp_var(char *var_name, char *key, int var_size)
{
	int	i;

	i = 0;
	while (key[i] && i < var_size && var_name[i] == key[i])
		i++;
	// printf("%s\n", key);
	// printf("VAR SIZE : %d\n", var_size);
	// printf("I SIZE : %d\n", i);
	// printf("%.8s\n", var_name);
	if (i == var_size && key[i] == 0)
	{
		// printf(" i = %d && varsize = %d\n", i, var_size);
		return (0);
	}
	return (1);
}

int	check_quotes(char quote, int *index, int *quote_state)
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
	else
		return (0);
	return (1);
}

char	*interrogation_mark(t_main *msh)
{
	// dprintf(2, "msh->code_status = %d\n", msh->code_status);
	// return (msh->code_status);
	// else if (str[i] != '$')
	// {
	// 	//printf("HERE\n");
	// 	printf("%c: command not found\n", str[i]);
	// 	return (0);
	// }
	// message d'erreur gere dans l'exec ? 
	return (ft_itoa(msh->code_status));
}

char	*ft_expand(t_main *msh, char *arg, t_env *env)
{
	int		i;
	int		quote_state;
	int		quote_true;
	int		var_size;
	//int		res_index;
	char	*res;
	t_env	*cpy;
	t_size	line;

	i = 0;
	quote_state = NO_QUOTE;
	quote_true = 0;
	var_size = 0;
	//res_index = 0;
	res = NULL;
	line.capacity = 0;
	line.line_size = 0;
	line.line = NULL;
	// printf("F :%d\n", ft_strlen(arg));
	while (arg[i] && arg[i] != '\0')
	{
		if (quote_state != NO_QUOTE)
			quote_true = 1;
		if (arg[i] == '\'' || arg[i] == '"')
		{
			if (check_quotes(arg[i], &i, &quote_state))
				continue ;
		}
		if (arg[i] == '$' && arg[i + 1] != '\0' && quote_state != SINGLE_QUOTE) //gerer le else si ce n'est pas un dollar, cpier juste caractere dasn variable
		{
			i++;
			// printf("I = %d\n", i);
			if (arg[i] == '?')
			{
				res = interrogation_mark(msh);
				add_size_to_str(&line, res);
				free(res);
				i++;
			}
			else if (ft_isalpha(arg[i]) || arg[i] == '_')
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
						if (!add_size_to_str(&line, cpy->value))
							return (NULL);
						break ;
					}
					cpy = cpy->next;
				}
				i += var_size;
			}
		}
		else
		{
			if (!add_size(&line, arg[i]))
				return (NULL);
			i++;
		}
		printf("I : %d\n", i);
	}
	printf("size == %d, line == %s quote == %d\n", line.line_size, line.line, quote_true);
	if (line.line_size == 0 && quote_true != 0)
	{
		line.line = malloc(1);
		line.line[0] = 0;
	}
	printf("RESULT : %s\n", line.line);
	return (line.line);
}

//corriger le malloc 2500
//gerer sigles et double quotes