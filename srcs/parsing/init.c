/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:48:35 by evlim             #+#    #+#             */
/*   Updated: 2024/12/11 09:00:09 by evlim            ###   ########.fr       */
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

void	ft_init_data(t_main *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_main));
	msh->env = get_env(envp);
}

void	ft_init_data_bis(t_main *msh)
{
	int	in;
	int	out;

	in = msh->stdin_copy;
	out = msh->stdout_copy;
	msh->pipefd[1] = -1;
	msh->pipefd[0] = -1;
	msh->prev_pipe = msh->pipefd[0];
	msh->stdin_copy = in;
	msh->stdout_copy = out;
	msh->file = -1;
}
