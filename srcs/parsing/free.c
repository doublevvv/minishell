/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:31:31 by evlim             #+#    #+#             */
/*   Updated: 2024/12/11 18:36:34 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_error_message(int i, char c)
{
	if (i == ALLOCATION_FAILED)
	{
		ft_putstr_fd("Failed to allocate memory\n", 2);
	}
	else if (i == UNCLOSED_QUOTE)
	{
		ft_putstr_fd("unexpected EOF while looking for matching quotes\n", 2);
	}
	else if (i == EMPTY_WORD)
	{
		if (c != '\0')
		{
			printf("syntax error near unexpected token `%c`\n", c);
		}
		else
		{
			ft_putstr_fd("syntax error: unexpected end of file\n", 2);
		}
	}
}

void	ft_free_lst(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*current;
	t_lst	*tmp_arg;

	current = *lst;
	while (current != NULL)
	{
		tmp_arg = current->u_data.cmd_args;
		while (tmp_arg != NULL)
		{
			if (tmp_arg->token_type != REDIRECTION_HEREDOC && tmp_arg->u_data.word != NULL)
			{
				free(tmp_arg->u_data.word);
			}
			tmp = tmp_arg->next;
			free(tmp_arg);
			tmp_arg = tmp;
		}
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

void	ft_free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_free_all(t_main *msh, char *error/*, bool exit*/)//rajouter un parametre indiquant si le shell doit exit ou non et faire un if(exit != false) free l'env et exit dans des accolades
{
	dprintf(2, "\t\t\ton passe dans la fonction qui frree\n");
	dprintf(2, "\t\t\tici on free le pid : %d et le tab qui free pas et a %p\n", getpid(), msh->cmd_array);
	if (error != NULL)
	{
		perror(error);
	}
	if (msh->paths != NULL)
	{
		ft_free_double_array(msh->paths);
		msh->paths = NULL;
	}
	if (msh->cmd_array != NULL)
	{
		//dprintf(2, "\t\t\tici on free le pid : %d et le tab qui free pas et a %p\n", getpid(), msh->cmd_array);
		free(msh->cmd_array);
		//ft_free_double_array(msh->cmd_array);
		msh->cmd_array = NULL;
	}
	if (msh->envp != NULL)
	{
		ft_free_double_array(msh->envp);
		msh->envp = NULL;
	}
	if (msh->head_command != NULL)
	{
		ft_free_lst(&msh->head_command);
	}
	if (msh->line != NULL)
	{
		free(msh->line);
		msh->line = NULL;
	}
	if (msh->stdin_copy != -1)
		close(msh->stdin_copy);
	if (msh->stdout_copy != -1)
		close(msh->stdout_copy);
	//lst_env_clear(&msh->env);
}
