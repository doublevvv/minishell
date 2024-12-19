/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:39:10 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/19 08:38:13 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_code_case(t_main *msh, t_expand_vars *vars)
{
	char	*res;

	res = ft_itoa(msh->code_status);
	if (!res)
	{
		free(vars->line.line);
		ft_free_all(msh, "malloc failure", true);
	}
	if (!add_size_to_str(&vars->line, res))
		fail_alloc_expand(msh, &vars->line, res);
	free(res);
	return (1);
}

int	fill_var(t_main *msh, t_expand_vars *vars, int i)
{
	int	var_size;

	if (vars->arg[i] == '?')
		return (exit_code_case(msh, vars));
	else if (ft_isalpha(vars->arg[i]) || vars->arg[i] == '_')
	{
		var_size = 1;
		while (ft_isalnum(vars->arg[i + var_size])
			|| vars->arg[i + var_size] == '_')
			var_size++;
		while (vars->cpy)
		{
			if (comp_var(vars->arg + i, vars->cpy->key, var_size) == 0)
			{
				if (!add_size_to_str(&vars->line, vars->cpy->value))
					fail_alloc_expand(msh, &vars->line, NULL);
				break ;
			}
			vars->cpy = vars->cpy->next;
		}
		return (var_size);
	}
	return (0);
}

void	expand_loop(t_main *msh, int *i, t_env *env, t_expand_vars *q_vars)
{
	q_vars->cpy = env;
	if (q_vars->quote_state != NO_QUOTE)
		q_vars->quote_true = 1;
	if (q_vars->arg[*i] == '\'' || q_vars->arg[*i] == '"')
	{
		if (check_quotes(q_vars->arg[*i], i, &q_vars->quote_state))
			return ;
	}
	if (q_vars->arg[*i] == '$' && q_vars->arg[*i + 1] != '\0'
		&& q_vars->quote_state != SINGLE_QUOTE)
	{
		(*i)++;
		*i += fill_var(msh, q_vars, *i);
	}
	else
	{
		if (!add_size(&q_vars->line, q_vars->arg[*i]))
			fail_alloc_expand(msh, &q_vars->line, NULL);
		(*i)++;
	}
}

char	*ft_expand(t_main *msh, char *arg, t_env *env)
{
	int				i;
	t_expand_vars	q_vars;

	q_vars.arg = arg;
	i = 0;
	q_vars.quote_true = 0;
	q_vars.quote_state = NO_QUOTE;
	q_vars.line.capacity = 0;
	q_vars.line.line_size = 0;
	q_vars.line.line = NULL;
	while (arg[i] && arg[i] != '\0')
		expand_loop(msh, &i, env, &q_vars);
	if (q_vars.line.line_size == 0 && q_vars.quote_true != 0)
	{
		q_vars.line.line = malloc(1);
		q_vars.line.line[0] = 0;
	}
	return (q_vars.line.line);
}
