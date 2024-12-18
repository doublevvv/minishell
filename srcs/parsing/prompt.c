/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 17:37:49 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* The ft_execute_builtin() function calls the corresponding builtin command's 
function and updates the code status accordingly. */
void	ft_execute_builtin(t_main *msh, int i)
{
	if (i == ECHO)
		msh->code_status = ft_echo(msh, msh->env);
	else if (i == CD)
		msh->code_status = ft_cd(msh, msh->env);
	else if (i == PWD)
		msh->code_status = ft_pwd(msh, NULL);
	else if (i == EXPORT)
		msh->code_status = ft_export(msh, msh->env);
	else if (i == UNSET)
		msh->code_status = ft_unset(msh, msh->env);
	else if (i == ENV)
		ft_env(msh->env);
	else if (i == EXIT)
		msh->code_status = ft_exit(msh, NULL);
}

/* The ft_is_builtin() function checks whether the given string matches one of 
the builtin commands and returns the corresponding index of the command in the 
builtin array. If the command is not found, it returns -1. */
int	ft_is_builtin(char *str)
{
	int			i;
	int			builtin_found;
	const char	*builtin[] = {"echo", "cd", "pwd", "export", \
		"unset", "env", "exit", NULL};

	i = 0;
	builtin_found = -1;
	while (builtin[i] != NULL)
	{
		if (ft_strcmp(builtin[i], str) == 0)
		{
			builtin_found = i;
			break ;
		}
		i++;
	}
	return (builtin_found);
}

void	ft_copy_stdin_stdout(t_main *msh)
{
	msh->stdin_copy = dup(STDIN_FILENO);
	msh->stdout_copy = dup(STDOUT_FILENO);
	if (msh->stdin_copy == -1 || msh->stdout_copy == -1)
	{
		ft_free_all(msh, "Failed to dup stdin/stdout", true);
	}
}

void	ft_handle_signal_in_loop(t_main *msh)
{
	if (msh->is_signal == false)
	{
		printf("\n");
		msh->is_signal = true;
	}
	msh->code_status = 130;
	g_signal_global = 0;
	if (dup2(msh->stdin_copy, STDIN_FILENO) == -1)
	{
		ft_free_all(msh, NULL, true);
	}
	close(msh->stdin_copy);
	close(msh->stdout_copy);
}

void	ft_msh_loop(t_main *msh)
{
	while (1)
	{
		set_signal();
		ft_copy_stdin_stdout(msh);
		ft_init_data_bis(msh);
		msh->line = readline("les loutres > ");
		if (g_signal_global != 0)
		{
			ft_handle_signal_in_loop(msh);
			continue ;
		}
		if (!msh->line)
			ft_free_all(msh, NULL, true);
		add_history(msh->line);
		if (ft_check_prompt(msh, msh->line) == false)
		{
			g_signal_global = 0;
			ft_free_all(msh, NULL, false);
		}
		else
			ft_exec(msh);
	}
	rl_clear_history();
}
