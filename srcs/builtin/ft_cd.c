/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:39:45 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/19 08:01:26 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_home(t_main *msh, t_env *env)
{
	char	*home;
	t_env	*cpy;

	cpy = env;
	while (cpy)
	{
		if (ft_strnstr(cpy->key, "HOME", 6))
		{
			home = cpy->value;
			printf("PATH HOME : %s\n", home);
		}
		cpy = cpy->next;
	}
	if (msh->cmd_array[0] && (!msh->cmd_array[1] || (msh->cmd_array[1][0] == '~'
			&& msh->cmd_array[1][0] == 0)))
	{
		if (chdir(home) == -1)
		{
			write(2, "les loutres: cd: HOME not set\n",
				ft_strlen("les loutres: cd: HOME not set\n"));
			return (0);
		}
	}
	return (1);
}

int	ft_cd(t_main *msh, t_env *env)
{
	char	*path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (msh->cmd_array[1] && msh->cmd_array[2])
	{
		write(2, "les loutres: cd: too many arguments\n", 37);
		return (0);
	}
	get_home(msh, env);
	if (msh->cmd_array[1])
	{
		if (chdir(msh->cmd_array[1]) == -1)
			return (ft_printf(2,
					"les loutres: cd: %s: No such file or directory\n",
					msh->cmd_array[1]));
		path = getcwd(NULL, 0);
		if (!path)
		{
			ft_print_error_message(ALLOCATION_FAILED, 0);
			ft_free_all(msh, NULL, true);
		}
	}
	return (0);
}
