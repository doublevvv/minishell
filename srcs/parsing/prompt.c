/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/16 11:09:37 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_prompt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 2] == '|')
		{
			printf("syntax error unexpected token `%c`\n", str[i]);
			exit (1);
		}
		if (str[i] == '>' && str[i + 2] == '>')
		{
			printf("syntax error unexpected token `%c`\n", str[i]);
			exit (1);
		}
		if (str[i] == '<' && str[i + 2] == '<')
		{
			printf("syntax error unexpected token `%c`\n", str[i]);
			exit (1);
		}
		i++;
	}
	return (0);
}

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

// void	ft_assign_type(t_main *msh)
// {
// 	int		i;
// 	int		j;
// 	t_lst	*tmp;

// 	i = 0;
// 	tmp = msh->cmd_lst;
// 	while (tmp != NULL)
// 	{
// 		while (tmp->cmd_name[i] != NULL)
// 		{
// 			j = 0;
// 			while (tmp->cmd_name[i][j] != '\0')
// 			{
// 				if (tmp->cmd_name[i][j] == '|')
// 				{
// 					msh->token = PIPE;
// 					printf("Je suis un pipe\n");
// 					printf("valeur token = %d\n", msh->token);
// 					printf("adresse valeur token = %p\n", &msh->token);
// 				}
// 				else if (tmp->cmd_name[i][j] == '>')
// 				{
// 					msh->token = REDIRECTION;
// 					printf("Je suis une redirection droite\n");
// 					printf("valeur token = %d\n", msh->token);
// 					printf("adresse valeur token = %p\n", &msh->token);
// 				}
// 				else if (tmp->cmd_name[i][j] == '<')
// 				{
// 					msh->token = REDIRECTION;
// 					printf("Je suis une redirection gauche\n");
// 					printf("valeur token = %d\n", msh->token);
// 					printf("adresse valeur token = %p\n", &msh->token);
// 				}
// 				else if (tmp->cmd_name[i][j] != '|' && tmp->cmd_name[i][j] != '>')
// 				{
// 					msh->token = CMD;
// 					printf("Je suis une commande\n");
// 					printf("valeur token = %d\n", msh->token);
// 					printf("adresse valeur token = %p\n", &msh->token);
// 				}
// 				j++;
// 			}
// 			tmp->type = msh->token;
// 			i++;
// 			printf("ICI valeur token = %d\n", msh->token);
// 		}
// 		tmp = tmp->next;
// 	}
// }

char	display_prompt(t_main *msh, t_redir *lst_redirection)
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
		check_prompt(line);
		if (ft_check_quotes(msh, line) == 0)
		{
			printf("syntax error: unexpected end of file");
			free(line);
			exit (1);
		}
		msh->cmd = ft_split_pipe(line, '|');
		if (msh->cmd == NULL)
		{
			free(line);
			exit (1);
		}
		i = 0;
		while (msh->cmd[i])
		{
			printf("cmd = %s\n", msh->cmd[i]);
			i++;
		}
		ft_add_cmd_to_lst(msh);
		ft_display_lst(msh);
		ft_check_redirection(msh, lst_redirection);
		printf("-------------LISTE REDIRECTION-----------\n");
		ft_add_redirection_to_lst(lst_redirection);
		ft_display_lst_redir(lst_redirection);
	}
}
