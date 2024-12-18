/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:41:51 by evlim             #+#    #+#             */
/*   Updated: 2024/12/18 12:53:35 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_create_cmd_array(t_main *msh, t_lst *cmd)
{
	char	*expand_result;

	msh->nb_cmd_array = 0;
	while (cmd != NULL)
	{
		if (cmd->token_type == WORD)
		{
			expand_result = ft_expand(msh, cmd->u_data.word, msh->env);
			free(cmd->u_data.word);
			cmd->u_data.word = expand_result;
			if (cmd->u_data.word != NULL)
			{
				msh->nb_cmd_array++;
			}
		}
		cmd = cmd->next;
	}
	msh->cmd_array = malloc((msh->nb_cmd_array + 1) * sizeof(char *));
	if (!msh->cmd_array)
	{
		close(msh->pipefd[0]);
		close(msh->pipefd[1]);
		ft_putstr_fd("Failed to create commands array\n", 2);
		ft_free_all(msh, NULL, true);
	}
}

/*void	ft_display_cmd_array(t_main *msh)
{
	int	i;

	i = 0;
	dprintf(2, "Array of commands\n");
	while (msh->cmd_array[i] != NULL)
	{
		dprintf(2, "cmd %d : %s\n", i, msh->cmd_array[i]);
		i++;
	}
}*/
