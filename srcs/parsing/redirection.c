/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:56:54 by evlim             #+#    #+#             */
/*   Updated: 2024/10/16 11:16:38 by evlim            ###   ########.fr       */
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

void	ft_check_redirection(t_main *msh, t_redir *lst_redirection)
{
	(void)*lst_redirection;
	int		i;
	t_lst	*tmp;
	char	*redir;

	i = 0;
	tmp = msh->cmd_lst;
	while (tmp != NULL)
	{
		while (tmp->cmd_name[i] != NULL)
		{
			redir = ft_strstr(tmp->cmd_name[i], ">");
			printf("on recupere => %s\n", redir);
			i++;
		}
		ft_lstnew_redir(redir);
		tmp = tmp->next;
	}
}
