/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:39:45 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/11/21 16:53:48 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// 	path = getcwd(current_directory, PATH_MAX);
// 	chdir(path);
// 	if (chdir(path) == -1)
// 	{
// 		perror("Error ");
// 	}

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

int	ft_cd(char **arg, char **env, t_env **environ)
{
	int i;
	char *home;
	char *path;
	char *old_path;
	t_env	*cpy;

	cpy->cpy = *environ;
	old_path = getcwd(NULL, 0);
	printf("PATH : %s\n", old_path);
	i = 0;
	while (env[i] != NULL)
	{
		home = ft_strnstr(env[i], "HOME=", 5);
		if (home != NULL)
			break;
		i++;
	}
	printf("%s\n", home);
	if (strncmp("cd", arg[0], 3) != 0)
	{
		printf("%s: command not found\n", arg[0]);
		return (0);
	}
	if (arg[0] && !arg[1])
	{
		//printf("here\n");
		if (chdir(home) == -1)
		{
			printf("les loutres: cd: HOME not set\n");
			return (0);
		}
	}
	if (arg[1])
	{
		if (chdir(arg[1]) == -1)
			return(printf("les loutres: cd: %s: No such file or directory\n", arg[1]));
		if (arg[1] && arg[2])
		{
			write(1, "les loutres: cd: too many arguments\n", 37);
			return (0);
		}
		path = getcwd(arg[1], PATH_MAX);
		if (ft_strnstr(cpy->key, "OLDPWD", 6))
			cpy->value = old_path;
		printf("%s\n", cpy->value);;
	}
	return (0);
}
