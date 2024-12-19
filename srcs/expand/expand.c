/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:32 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 20:51:40 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_size(t_size *line, char c)
{
	char	*tmp;

	if (line->capacity == 0 || line->line_size == line->capacity)
	{
		if (line->capacity != 0)
			line->capacity = line->capacity * 3;
		else
			line->capacity = 20;
		tmp = malloc(sizeof(char) * (line->capacity + 1));
		if (!tmp)
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
	if (i == var_size && key[i] == 0)
		return (0);
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

void	fail_alloc_expand(t_main *msh, t_size *line, char *res)
{
	free(line->line);
	free(res);
	ft_free_all(msh, "malloc failure", true);
}
