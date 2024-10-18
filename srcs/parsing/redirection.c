/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:56:54 by evlim             #+#    #+#             */
/*   Updated: 2024/10/18 15:36:36 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	ft_is_redirection(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '>' || str[i] == '<')
// 		{
// 			if (str[i - 2] >= 'a' && str[i - 2] <= 'z' && str[i + 2] >= 'a' && str[i + 2] <= 'z')
// 				return (1);
// 			else if ((str[i - 2] == '"' || str[i - 2] == '\'') && (str[i + 2] == '"' || str[i + 2] == '\''))
// 				return (1);
// 			else if ((str[i - 2] == '"' || str[i - 2] == '\'') || (str[i + 2] == '"' || str[i + 2] == '\''))
// 				return (1);
// 			else if (str[i] == '<' && str[i + 1] == '<')
// 				return (1);
// 			else if (str[i] == '>' && str[i + 1] == '>')
// 				return (1);
// 			else
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// void	ft_redir_sep(t_redir *lst_redirection)
// {
// 	char	**linked_list;
// 	int		i;
// 	t_redir	*tmp;

// 	linked_list = ft_split_redir(lst_redirection->token, '>');
// 	i = 0;
// 	while (linked_list[i] != NULL)
// 	{
// 		if (i == 0)
// 		{
// 			lst_redirection->token = linked_list[i];
// 			i++;
// 			printf("token = %s\n", lst_redirection->token);
// 			lst_redirection->file = linked_list[i];
// 			i++;
// 			printf("file = %s\n", lst_redirection->file);
// 		}
// 		else
// 		{
// 			tmp = ft_lstnew_redir(linked_list[i], linked_list[i + 1]);
// 			ft_lstadd_back_redir(&lst_redirection, tmp);
// 			i += 2;
// 		}
// 	}
// }

void	ft_redir_sep(t_redir *lst_redirection)
{
	char	*redir_token;
	t_redir	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = lst_redirection;
	while (tmp != NULL)
	{
		redir_token = tmp->token;
		if (i == 0)
		{
			lst_redirection->token = ft_strdup(">");
			printf("token1 = %s\n", lst_redirection->token);
			lst_redirection->file = ft_strdup(redir_token + 1);
			printf("file1 = %s\n", lst_redirection->file);
		}
		else
		{
			tmp = ft_lstnew_redir(&redir_token[i], &redir_token[i + 1]);
			ft_lstadd_back_redir(&lst_redirection, tmp);
			i += 2;
		}
		tmp = tmp->next;
	}
}

// void	ft_redir_sep(t_main *msh)
// {
// 	// t_r	*tmp;
// 	// char	*redir_token;
// 	char	*file_name;

// 	// tmp = ;
// 	// while (tmp != NULL)
// 	// {
//     // //     lst_redirection->file = ft_strdup(lst_redirection->token + 1);
//     // //     lst_redirection->token = ft_strdup(">");
//     // //     tmp = tmp->next;
//     // // }
// 	// 	redir_token = tmp->token;
// 	// 	if (redir_token[0] == '>')
// 	// 	{
// 	// 		file_name = redir_token + 1;
// 	// 		tmp->token = ft_strdup(">");
// 	// 		tmp->file = ft_strdup(file_name);
// 	// 	}
// 	// 	tmp = tmp->next;
// 	// }
// 	if (msh->redir[0] == '>')
// 	{
// 		msh->type = REDIRECTION_RIGHT;
// 		file_name = msh->redir + 1;
// 		msh->token = ft_strdup(">");
// 		printf("msh->token = %s\n", msh->token);
// 		msh->filename = ft_strdup(file_name);
// 		printf("msh->filename = %s\n", msh->filename);
// 	}
// }

void	ft_check_redirection(t_main *msh, t_redir **lst_redirection)
{
	int		i;
	int		j;
	t_lst	*tmp;

	i = 0;
	j = 0;
	tmp = msh->cmd_lst;
	while (tmp != NULL)
	{
		while (tmp->cmd_name[i] != NULL)
		{
			printf("cmd name = %s\n", tmp->cmd_name[i]);
			msh->redir = ft_strstr(tmp->cmd_name[i], ">");
			printf("on recupere => %s\n", msh->redir);
			printf("-----------------------\n");
			ft_add_redirection_to_lst(msh, lst_redirection);
			i++;
		}
		tmp = tmp->next;
	}
}
