/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:39:45 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/17 10:19:38 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Fonction non utilisee
int	old_path(t_env *env, char *old_directory)
{
	t_env	*tmp;
	char	*cpy;

	tmp = env;
	while (tmp)
	{
		if (ft_strnstr(tmp->key, "OLDPWD", 6))
		{
			printf("%s\n", tmp->key);
			if (tmp->value)
				free(tmp->value);
			cpy = ft_strjoin("OLDPWD=", old_directory);
			if (!cpy)
			{
				;
			}
			//proteger
		}
	}
	return (0);
}
// Return nb ?
int	ft_cd(t_main *msh, t_env *env)
{
    char	*home;
    char	*path;
    char	*old_path;
    t_env	*cpy;

	cpy = env;
	old_path = getcwd(NULL, 0);
	if (msh->cmd_array[1] && msh->cmd_array[2])
	{
		write(2, "les loutres: cd: too many arguments\n", 37);
		return (0);
	}
	// printf("PATH : %s\n", old_path);
    // while (cpy)
    // {
    //     printf("key : %s, value : %s\n", cpy->key, cpy->value);
    //     cpy = cpy->next;
    // }
	if (ft_strncmp("cd", msh->cmd_array[0], 3) != 0)
	{
		ft_print_cmd_msg_error(msh, 1);
		return (0);
	}
	while (cpy)
	{
		if (ft_strnstr(cpy->key, "HOME", 6))
		{
			home = cpy->value;
			// printf("PATH HOME : %s\n", home);
		}
		cpy = cpy->next;
	}
	if (msh->cmd_array[0] && (!msh->cmd_array[1] || (msh->cmd_array[1][0] == '~' && msh->cmd_array[1][0] == 0)))
	{
		if (chdir(home) == -1)
		{
			write(2, "les loutres: cd: HOME not set\n", ft_strlen("les loutres: cd: HOME not set\n"));
			return (0);
		}
	}
	if (msh->cmd_array[1])
	{
        // if (arg[1] == '~')
        // {
        //     printf("HELLO\n");
        //     chdir(home);//proteger chdir // proteger home?
        // }
		if (chdir(msh->cmd_array[1]) == -1)
			return(printf("les loutres: cd: %s: No such file or directory\n", msh->cmd_array[1]));//a mettre sur la sortie d'erreur
		path = getcwd(NULL, 0);
		if (!path)
		{
			ft_print_error_message(ALLOCATION_FAILED, 0);
			ft_free_all(msh, NULL, true);
		}
		// printf("OLD : %s\n", old_path);
		while (cpy)
		{
			if (ft_strnstr(cpy->key, "OLDPWD", 6))
			{
				cpy->value = old_path;
				// printf("LST VALUE : %s\n", cpy->value);
			}
			cpy = cpy->next;
		}
		// printf("HERE e: %s\n", path);
	}
	return (0);
}
