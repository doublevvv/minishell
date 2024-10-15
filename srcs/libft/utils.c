/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:36:14 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/10/10 15:17:04 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

void	ft_display_lst(t_main *msh)
{
	int		i;
	t_lst	*tmp;

	tmp = msh->cmd_lst;
	printf("DANS LISTE\n");
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->cmd_name[i] != NULL)
		{
			printf("%d | %s\n", i, tmp->cmd_name[i]);
			printf("valeur type = %d\n", tmp->type);
			i++;
		}
		tmp = tmp->next;
	}
	printf("----------------------------------\n");
}

t_lst	*ft_lstnew(char **name, int token)
{
	t_lst	*new_node;

	new_node = malloc(sizeof(t_lst));
	if (!new_node)
		return (NULL);
	new_node->cmd_name = name;
	new_node->type = token;
	printf("type = %d\n", new_node->type);
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (!new)
	{
		//free
	}
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	ft_add_cmd_to_lst(t_main *msh)
{
	printf("msh token = %d\n", msh->token);
	ft_lstadd_back(&msh->cmd_lst, ft_lstnew(msh->cmd, msh->token));
}

int	ft_is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

// int	check_incorrect_signs(char c)
// {
// 	if (c != '\'' || c != '"' || c != "|" || c != '>' || c != '<' || c != '$' /
// 		(c <= 'a' && c >= 'z'))
// 		return (0);
// 	return (1);
// }

int	ft_is_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i - 2] >= 'a' && str[i - 2] <= 'z' && str[i + 2] >= 'a' && str[i + 2] <= 'z')
				return (1);
			else if ((str[i - 2] == '"' || str[i - 2] == '\'') && (str[i + 2] == '"' || str[i + 2] == '\''))
				return (1);
			else if ((str[i - 2] == '"' || str[i - 2] == '\'') || (str[i + 2] == '"' || str[i + 2] == '\''))
				return (1);
			else if (str[i] == '<' && str[i + 1] == '<')
				return (1);
			else if (str[i] == '>' && str[i + 1] == '>')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (1);
}
