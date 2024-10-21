/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/21 16:02:47 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_check_prompt(char *str)
{
	//ft_check_token(str);
	ft_is_redirection(str);
	// int	i;

	// i = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '|' && str[i + 2] == '|')
	// 	{
	// 		printf("syntax error unexpected token `%c`\n", str[i]);
	// 		exit (1);
	// 	}
	// 	if (str[i] == '>' && str[i + 2] == '>')
	// 	{
	// 		printf("syntax error unexpected token `%c`\n", str[i]);
	// 		exit (1);
	// 	}
	// 	if (str[i] == '<' && str[i + 2] == '<')
	// 	{
	// 		printf("syntax error unexpected token `%c`\n", str[i]);
	// 		exit (1);
	// 	}
	// 	i++;
	// }
	// return (0);
}

// bool	ft_check_quotes(t_main *msh, char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			printf("found double quotes\n");
// 			while (str[i] != '\0' && str[i] != '"')
// 			{
// 				i++;
// 			}
// 			if (str[i] == '"')
// 			{
// 				printf("double quote fermante FOUND\n");
// 				msh->double_quote = true;
// 			}
// 			else
// 			{
// 				printf("double quote fermante NOT FOUND\n");
// 				msh->double_quote = false;
// 			}
// 		}
// 		else if (str[i] == '\'')
// 		{
// 			i++;
// 			printf("found double quotes\n");
// 			while (str[i] != '\0' && str[i] != '\'')
// 			{
// 				i++;
// 			}
// 			if (str[i] == '\'')
// 			{
// 				printf("double quote fermante FOUND\n");
// 				msh->double_quote = true;
// 			}
// 			else
// 			{
// 				printf("double quote fermante NOT FOUND\n");
// 				msh->double_quote = false;
// 			}
// 		}
// 		i++;
// 	}
// 	if (msh->double_quote == true)
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

char	ft_display_prompt(t_main *msh, t_redir *lst_redirection)
{
	(void)*lst_redirection;

	while (1)
	{
		msh->line = readline("les loutres > ");
		if (!msh->line)
		{
			exit (1);
		}
		add_history(msh->line);
		ft_check_prompt(msh->line);
		// if (ft_check_quotes(msh, line) == 0)
		// {
		// 	printf("syntax error: unexpected end of file");
		// 	free(line);
		// 	exit (1);
		// }
		// msh->cmd = ft_split_pipe(line, '|');
		// if (msh->cmd == NULL)
		// {
		// 	free(line);
		// 	exit (1);
		// }
		// i = 0;
		// while (msh->cmd[i])
		// {
		// 	printf("cmd = %s\n", msh->cmd[i]);
		// 	i++;
		// }
		// ft_add_cmd_to_lst(msh);
		// printf("-------------LISTE REDIRECTION-----------\n");
		// ft_display_lst(msh);
		// ft_check_redirection(msh, &lst_redirection);
		// ft_display_lst_redir(lst_redirection);
		// printf("-------------LISTE REDIRECTION APRES SPLIT ENTRE TOKEN ET FILENAME-----------\n");
		// ft_redir_sep(lst_redirection);
		// ft_display_lst_redir(lst_redirection);
	}
}

// void	ft_free_double_array(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	tab = NULL;
// }

// void	ft_free_all(t_cmd *pipex, char *error)
// {
// 	if (error != NULL)
// 	{
// 		perror(error);
// 	}
// 	if (pipex->paths != NULL)
// 	{
// 		ft_free_double_array(pipex->paths);
// 	}
// 	exit(1);
// }

// void	ft_check_error_malloc(t_cmd *pipex)
// {
// 	ft_free_all(pipex, NULL);
// }
