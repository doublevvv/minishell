/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/11 17:55:47 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_check_quotes(t_main *msh, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			printf("found double quotes\n");
			while (str[i] != '\0' && str[i] != '"')
			{
				i++;
			}
			if (str[i] == '"')
			{
				printf("double quote fermante FOUND\n");
				msh->double_quote = true;
			}
			else
			{
				printf("double quote fermante NOT FOUND\n");
				msh->double_quote = false;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			printf("found double quotes\n");
			while (str[i] != '\0' && str[i] != '\'')
			{
				i++;
			}
			if (str[i] == '\'')
			{
				printf("double quote fermante FOUND\n");
				msh->double_quote = true;
			}
			else
			{
				printf("double quote fermante NOT FOUND\n");
				msh->double_quote = false;
			}
		}
		i++;
	}
	if (msh->double_quote == true)
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
					msh->token = PIPE;
					printf("Je suis une pipe\n");
					printf("valeur token = %d\n", msh->token);
				}
				else if (tmp->cmd_name[i][j] == '>')
				{
					msh->token = REDIRECTION;
					printf("Je suis une redirection droite\n");
					printf("valeur token = %d\n", msh->token);
				}
				else if (tmp->cmd_name[i][j] == '<')
				{
					msh->token = REDIRECTION;
					printf("Je suis une redirection gauche\n");
					printf("valeur token = %d\n", msh->token);
				}
				else if (tmp->cmd_name[i][j] != '|' && tmp->cmd_name[i][j] != '>')
				{
					msh->token = CMD;
					printf("Je suis une commande\n");
					printf("valeur token = %d\n", msh->token);
				}
				j++;
			}
			i++;
			printf("ICI valeur token = %d\n", msh->token);
			t_lst  *lst;
			lst = ft_lstnew(msh->cmd, msh->token);
		}
		tmp = tmp->next;
	}
}
char	display_prompt(t_main *msh)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("les loutres > ");
		if (!line)
		{
			exit (1);
		}
		add_history(line);
		i = 0;
		while (line[i])
		{
			if ((line[i] == '|' && line[i + 1] == '|') || (line[i] == '|' && line[i + 2] == '|'))
			{
				printf("syntax error unexpected token `%c`\n", line[i]);
				exit (1);
			}
			i++;
		}
		if (ft_check_quotes(msh, line) == 0)
		{
			printf("syntax error: unexpected end of file");
			exit (1);
		}
		// if (ft_is_redirection(line) == 0)
		// {
		// 	printf("syntax error near unexpected token `newline'");
		// 	exit (1);
		// }
		printf("line = %s\n", line);
		msh->tab_pipe = ft_split_pipe(line, '|');
		if (msh->tab_pipe == NULL)
		{
			exit (1);
		}
		i = 0;
		while (msh->tab_pipe[i])
		{
			printf("cmd = %s\n", msh->tab_pipe[i]);
			i++;
		}
			i = 0;
		msh->cmd = ft_split_quote(msh->tab_pipe[i], ' ');
		if (msh->cmd == NULL)
		{
			// free
			exit (1);
		}
		i = 0;
		while (msh->cmd[i])
		{
			printf("cmd = %s\n", msh->cmd[i]);
			i++;
		}
		ft_add_cmd_to_lst(msh);
		printf("----------------------------------\n");
		ft_display_lst(msh);
		ft_assign_type(msh);
		//printf("----------LISTE AVEC TOKEN------------\n");
		ft_display_lst(msh);
		//return (*line);
	}
}
