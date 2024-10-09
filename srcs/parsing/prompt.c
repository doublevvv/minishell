/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/09 15:38:38 by vlaggoun         ###   ########.fr       */
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
	if ((count_double_quotes % 2 == 0) && (count_simple_quotes % 2 == 0))
	{
		return (true);
	}
	return (false);
}

void	ft_assign_type(t_main *msh)
{
	int		i;
	int		j;
	t_lst	*tmp;

	i = 0;
	tmp = msh->cmd_lst;
	while (tmp != NULL)
	{
		while (tmp->cmd_name[i] != NULL)
		{
			j = 0;
			while (tmp->cmd_name[i][j] != '\0')
			{
				if (tmp->cmd_name[i][j] == '|')
				{
					tmp->type = PIPE;
					printf("Je suis une pipe\n");
					printf("valeur type = %d\n", tmp->type);
				}
				else if (tmp->cmd_name[i][j] == '>')
				{
					tmp->type = REDIRECTION;
					printf("Je suis une redirection\n");
					printf("valeur type = %d\n", tmp->type);
				}
				else if (tmp->cmd_name[i][j] != '|' && tmp->cmd_name[i][j] != '>')
				{
					tmp->type = CMD;
					printf("Je suis une commande\n");
					printf("valeur type = %d\n", tmp->type);
				}
				j++;
			}
			i++;
		}
		tmp = tmp->next;
	}
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
		if (ft_is_redirection(line) == 0)
		{
			printf("syntax error near unexpected token `newline'");
			exit (1);	
		}
		printf("line = %s\n", line);
		msh->cmd = ft_split(line, ' ');
		if (msh->cmd == NULL)
		{
			exit (1);
		}
		int i = 0;
		while (msh->cmd[i])
		{
			printf("cmd = %s\n", msh->cmd[i]);
			i++;
		}
		ft_add_cmd_to_lst(msh);
		printf("----------------------------------\n");
		printf("DANS LISTE\n");
		ft_display_lst(msh);
		ft_assign_type(msh);
		//return (*line);
	}
}
