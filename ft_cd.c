/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:39:45 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/04 13:23:49 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	old_path(t_env **env, char *old_directory)
{
	t_env *tmp;
	char *cpy;
	
	tmp = *env;
	while (tmp)
	{
		if (ft_strnstr(tmp->key, "OLDPWD", 6))
		{
			printf("%s\n", tmp->key);
			if (tmp->value)
				free(tmp->value);
			cpy = ft_strjoin("OLDPWD=", old_directory);
			
		}
	}
	return (0);
}

int	ft_cd(char **arg, t_env **env)
{
	char *home;
	char *path;
	char *old_path;
	t_env	*cpy;

	cpy = *env;
	old_path = getcwd(NULL, 0);
	printf("PATH : %s\n", old_path);
	//printf("CPY :%p\n", cpy);
	while (cpy != NULL)
	{
		//printf("CLE : %s\n",cpy->key);
		if (ft_strnstr(cpy->key, "HOME", 4) != NULL)
			break;
		cpy = cpy->next;
	}
	if (ft_strncmp("cd", arg[0], 3) != 0)
	{
		printf("%s: command not found\n", arg[0]);
		return (0);
	}
	while (cpy)
	{
		if (ft_strnstr(cpy->key, "HOME", 6))
		{
			home = cpy->value;
			printf("PATH HOME : %s\n", home);
		}
		cpy = cpy->next;
	}
	if (arg[0] && !arg[1])
	{
		if (chdir(home) == -1)
		{
			printf("les loutres: cd: HOME not set\n");
			return (0);
		}
	}
	if (arg[1])
	{
		if (chdir(arg[1]) == '~')
			printf("HELLO\n");
		if (chdir(arg[1]) == -1)
			return(printf("les loutres: cd: %s: No such file or directory\n", arg[1]));
		if (arg[1] && arg[2])
		{
			write(1, "les loutres: cd: too many arguments\n", 37);
			return (0);
		}
		path = getcwd(NULL, 0);
		if (!path)
			return (0);
		//proteger path
		printf("OLD : %s\n", old_path);
		while (cpy)
		{
			if (ft_strnstr(cpy->key, "OLDPWD", 6))
			{
				cpy->value = old_path;
				printf("LST VALUE : %s\n", cpy->value);
			}
			cpy = cpy->next;
		}
		printf("HERE : %s\n", path);
	}
	return (0);
}

