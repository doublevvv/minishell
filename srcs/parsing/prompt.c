/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/07 15:20:15 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_check_quotes(t_main *msh, char *str)
{
	(void)*msh;
	int	i;
	int	count_double_quotes;
	int	count_simple_quotes;

	i = 0;
	count_double_quotes = 0;
	count_simple_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			printf("found double quotes\n");
			msh->double_quote = true;
			count_double_quotes++;
			printf("nb double quote = %d\n", count_double_quotes);
		}
		if (str[i] == 39)
		{
			printf("found simple quotes\n");
			msh->simple_quote = true;
			count_simple_quotes++;
			printf("nb simple quote = %d\n", count_simple_quotes);
		}
		i++;
	}
	if ((count_double_quotes % 2 == 0) || (count_simple_quotes % 2 == 0))
	{
		return (true);
	}
	return (false);
}

char	display_prompt(t_main *msh)
{
	char	*line;

	while (1)
	{
		line = readline("les loutres > ");
		if (!line)
		{
			exit (1);
		}
		add_history(line);
		if (ft_check_quotes(msh, line) == 0)
		{
			printf("odd nb of quotes");
			exit (1);
		}
		printf("line = %s\n", line);
		msh->cmd = ft_split(msh, line, ' ');
		if (msh->cmd == NULL)
		{
			exit (1);
		}
		ft_add_cmd_to_lst(msh);
		printf("----------------------------------\n");
		ft_display_lst(msh);
		//return (*line);
	}
}
