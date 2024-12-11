/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:41:13 by evlim             #+#    #+#             */
/*   Updated: 2024/12/11 18:44:50 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execute_command(t_main *msh)
{
	ft_convert_lst_to_tab(msh);
	ft_search_env_path(msh);
	if (ft_get_paths(msh) == false)
	{
		ft_free_all(msh, NULL);
	}
	if (ft_strchr(msh->cmd_array[0], '/') == 1)
	{
		msh->full_path = msh->cmd_array[0];
		//dprintf(2, "msh->full_path = %s\n", msh->full_path);
		ft_check_access(msh);
	}
	else
	{
		//dprintf(2, "CHERCHER CHEMIN\n");
		ft_check_path(msh);
		//dprintf(2, "msh->full_path = %s\n", msh->full_path);
	}
	//dprintf(2, "COMMANDE VALIDE\n");
	//Conversion liste chainee env en char **
	if (execve(msh->full_path, msh->cmd_array, msh->envp) == -1)
	{
		ft_free_all(msh, "execve failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_handle_redirections(t_main *msh, t_lst *cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args != NULL)
	{
		if (cmd_args->token_type != WORD)
		{
			ft_open_redir(msh, cmd_args);
			//ft_redirect_in_out(msh);
		}
		else
		{
			if (cmd_args->u_data.word != NULL)
			{
				msh->cmd_array[i] = cmd_args->u_data.word;
			//dprintf(2, "msh->cmd_array[%d] = %s\n", i, msh->cmd_array[i]);
				i++;
			}
		}
		// ft_close_fds(msh);
		cmd_args = cmd_args->next;
	}
	msh->cmd_array[i] = NULL;
}

void	ft_redirect_pipes(t_main *msh, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		ft_free_all(msh, "dup2 failed");
		exit(EXIT_FAILURE);
	}
}
//mettre aa -1 quand c'est close et dans le child fermer tout ce qui est pas a -1
void	ft_dup_pipes(t_main *msh, int nb)
{
	if (nb == 0)
	{
		dprintf(2, "First command in pipeline\n");
		//ft_redirect_pipes(msh, msh->pipefd[1], STDOUT_FILENO);
		dprintf(2, "\t\t\t\t\tmsh->pipefd[1] = %d\n", msh->pipefd[1]);
		if (msh->pipefd[1] > -1 && dup2(msh->pipefd[1], STDOUT_FILENO) == -1)
		{
			ft_free_all(msh, "1. dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(msh->pipefd[1]);
		msh->prev_pipe = -1;
		dprintf(2, "msh->pipefd[1] = %d closed\n", msh->pipefd[1]);
	}
	else if (nb == (msh->nb_cmd - 1))
	{
		dprintf(2, "Last command in pipeline\n");
		close(msh->pipefd[1]);
		msh->pipefd[1] = -1;
		dprintf(2, "msh->pipefd[1] = %d closed\n", msh->pipefd[1]);
		//ft_redirect_pipes(msh, msh->prev_pipe, STDIN_FILENO);
		dprintf(2, "\t\t\t\t\tmsh->prev_pipe = %d\n", msh->prev_pipe);
		if (msh->prev_pipe > -1 && dup2(msh->prev_pipe, STDIN_FILENO) == -1)
		{
			ft_free_all(msh, "2. dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(msh->prev_pipe);
		msh->prev_pipe = -1;
		dprintf(2, "msh->prev_pipe = %d closed\n", msh->prev_pipe);
		//close(msh->pipefd[0]);
	}
	else
	{
		dprintf(2, "Between first and last commands in pipeline\n");
		dprintf(2, "msh->pipefd[0] = %d closed\n", msh->pipefd[0]);
		//ft_redirect_pipes(msh, msh->prev_pipe, STDIN_FILENO);
		dprintf(2, "\t\t\t\t\tmsh->prev_pipe = %d\n", msh->prev_pipe);
		if (msh->prev_pipe > -1 && dup2(msh->prev_pipe, STDIN_FILENO) == -1)
		{
			ft_free_all(msh, "3. dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(msh->prev_pipe);
		msh->prev_pipe = -1;
		dprintf(2, "msh->prev_pipe = %d closed\n", msh->prev_pipe);
		//ft_redirect_pipes(msh, msh->pipefd[1], STDOUT_FILENO);
		dprintf(2, "\t\t\t\t\tmsh->pipefd[1] = %d\n", msh->pipefd[1]);
		if (msh->pipefd[1] > -1 && dup2(msh->pipefd[1], STDOUT_FILENO) == -1)
		{
			ft_free_all(msh, "4. dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(msh->pipefd[1]);
		msh->pipefd[1] = -1;
		dprintf(2, "msh->pipefd[1] = %d closed\n", msh->pipefd[1]);
	}
}

/* The ft_execute_child() function handles the execution of the command
in the child process.
The execve() function replaces the current process with a new process. It passes
all the informations to the process. */

//signal(SIGINT, SIG_IGN);//ignorer completemeent un signal
//signal(SIGINT, SIG_DFL);//restaure le comportement d'origine d'un signl

void	ft_handle_exec( t_main *msh, t_lst *tmp, int nb)
{
	t_lst	*tmp_arg;
	int		builtin;

	tmp_arg = tmp->u_data.cmd_args;
	if (msh->cmd_array)
		free(msh->cmd_array);
	ft_create_cmd_array(msh, tmp_arg);
	builtin = 0;
	if (msh->nb_cmd > 1)
	{
		ft_dup_pipes(msh, nb);
	}
	ft_handle_redirections(msh, tmp_arg);
	if (msh->cmd_array[0] == NULL)
	{
		return ;
	}
	builtin = ft_is_builtin(msh->cmd_array[0]);
	//dprintf(2, "builtin = %d\n", builtin);
	//dprintf(2, "nb = %d\n", nb);
	if (msh->in_pipeline == 0)
	{
		if (builtin != -1)
		{
			dprintf(2, "EN DEHORS DE PIPELINE\n");
			ft_execute_builtin(msh, builtin);
		}
		else
		{
			msh->in_pipeline = 1;
			tmp->pid = fork();
			if (tmp->pid == 0)
			{
				dprintf(2, "ONE COMMAND WITH/WITHOUT REDIRECTION\n");
				close(msh->stdin_copy);
				close(msh->stdout_copy);
				ft_execute_command(msh);
			}
		}
	}
	else
	{
		dprintf(2, "IN PIPELINE\n");
		tmp->pid = fork();
		dprintf(2, "\t\t\tici on fork\n");
		if (tmp->pid == 0)
		{
			dprintf(2, "\t\tProcess enfant au pid de : %d\n", getpid());
			if (builtin != -1)
			{
				ft_execute_builtin(msh, builtin);
				close(msh->stdin_copy);
				close(msh->stdout_copy);
				if (msh->pipefd[1] > -1)
				{
					close(msh->pipefd[1]);
				}
				if (msh->pipefd[0] > -1)
				{
					close(msh->pipefd[0]);
				}
				if (msh->prev_pipe > -1)
				{
					close(msh->prev_pipe);
				}
				ft_free_all(msh, NULL);
				exit(EXIT_SUCCESS);
			}
			else
			{
				close(msh->stdin_copy);
				close(msh->stdout_copy);
				if (msh->pipefd[1] > -1)
				{
					close(msh->pipefd[1]);
				}
				if (msh->pipefd[0] > -1)
				{
					close(msh->pipefd[0]);
				}
				if (msh->prev_pipe > -1)
				{
					close(msh->prev_pipe);
				}
				ft_execute_command(msh);
			}
		}
	}
}

// The ft_parent_wait() waits for the children processes to finish.
/*
WIFEXITED(wstatus)
	returns true if the child terminated normally,
    that is, by calling exit(3) or _exit(2), or by
    returning from main().

WEXITSTATUS(wstatus)
	returns the exit status of  the  child.
	This consists of the least significant 8 bits of
	the status argument that the child specified
	in a call to exit(3) or _exit(2) or as the argument
	for a return statement in main().
	This macro should be employed only if WIFEXITED returned true.

WIFSIGNALED(wstatus)
    returns true if the child process  was  terminated by a signal.

WTERMSIG(wstatus)
    returns  the  number of the signal that caused
    the child process to  terminate.
	This macro should be employed only if WIFSIGNALED returned true.
*/
void	ft_parent_wait(t_main *msh)
{
	t_lst	*cmd;
	int		status;

	status = 0;
	cmd = msh->head_command;
	while (cmd != NULL)
	{
		//dprintf(2, "cmd->pid = %d\n", cmd->pid);
		waitpid(cmd->pid, &status, 0);
		//dprintf(2, "word is %s\n", cmd->u_data.cmd_args->u_data.word);
		dprintf(2, "On a attendu le pid %d\n", cmd->pid);
		if (WIFEXITED(status))
		{
			msh->code_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			msh->code_status = WTERMSIG(status);
			msh->code_status += 128; // cf wait
		}
		cmd = cmd->next;
	}
}

void	ft_final_execution(t_main *msh)
{
	dprintf(2, "FINAL EXECUTION\n");
	if (msh->in_pipeline == 1)
	{
		ft_close_pipes_child(msh);
	}
	if (msh->in_pipeline == 1)
	{
		ft_parent_wait(msh);
	}
	ft_free_all(msh, NULL);
}

void	ft_count_cmds(t_main *msh, t_lst *lst)
{
	msh->nb_cmd = 0;

	while (lst != NULL)
	{
		msh->nb_cmd++;
		lst = lst->next;
	}
	dprintf(2, "TOTAL nb cmd = %d\n", msh->nb_cmd);
}

/* The ft_execution() function handles the execution of multiple commands,
manages the creation of pipes and processes. */
void	ft_exec(t_main *msh)
{
	t_lst	*tmp;
	int		i;

	tmp = msh->head_command;
	i = 0;
	ft_count_cmds(msh, tmp);
	while (tmp != NULL)
	{
		dprintf(2, "i = %d\n", i);
		dprintf(2, "msh->pipefd[1] = %d\n", msh->pipefd[1]);
		dprintf(2, "msh->pipefd[0] = %d\n", msh->pipefd[0]);
		dprintf(2, "msh->prev_pipe = %d\n", msh->prev_pipe);
		dprintf(2, "tmp->u.data.cmd_args->word = %s\n", tmp->u_data.cmd_args->u_data.word);
		if (tmp->next != NULL)
		{
			if (pipe(msh->pipefd) == -1)
			{
				ft_free_all(msh, "pipe failed");
				exit(EXIT_FAILURE);
			}
			msh->in_pipeline = 1;
		}
		dprintf(2, "AFTER PIPE \t\t\tmsh->pipefd[1] = %d\n", msh->pipefd[1]);
		dprintf(2, "AFTER PIPE \t\t\tmsh->pipefd[0] = %d\n", msh->pipefd[0]);
		dprintf(2, "AFTER PIPE \t\t\tmsh->prev_pipe = %d\n", msh->prev_pipe);
		ft_handle_exec(msh, tmp, i);
		if (msh->prev_pipe != -1)
		{
			close(msh->prev_pipe);
		}
		msh->prev_pipe = msh->pipefd[0];
		if (msh->pipefd[1] != -1)
		{
			close(msh->pipefd[1]);
		}
		i++;
		tmp = tmp->next;
		if (dup2(msh->stdout_copy, STDIN_FILENO) == -1 || dup2(msh->stdout_copy, STDOUT_FILENO) == -1)
		{
			ft_free_all(msh, "Failed to restore stdin/stdout");
			//penser a exit
		}
		//dprintf(2, "msh->stdin_copy = %d\n", msh->stdin_copy);
		//dprintf(2, "msh->stdout_copy = %d\n", msh->stdout_copy);
	}
	ft_final_execution(msh);
}

/* executer, si besoin creer un pipe, dup stdin stdout avec le pipe si necessaire,
si dans pipeline fork avant de lancer simplecommand
simple command:
	parcourir chaque noeud: 
		->faire l'expansion, 
		->si redir open et dup puis close le fd
		->si word et resultat de l'expansion non NULL ajouter au char ** de commande
check si builtin, si oui executer
check l'access (/?)
fork si necessaire(si dans pipeline le fork a deja ete fait) puis envoyer a execve
sauvegarder stdin stdout en debut de commande(dup) et les restaurer apres l'execution(dup2)
*/

// => chercher cas tab supprimee

//parcourir la liste faire expansion dup les redir construire le char **
//tester builtin , exec la builtin ou tester l'access et exec la cmd puis apres la boucle attendre toutes les commandes
//si ! pipeline et builtin ne pas fork faire la builtin et partir de la fct
//else fork dup pipe si builtin faire builtin sinon access et tout le tralala exit uniquemen dans ce else

//make re; valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=ignore ./minishell

/*
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
cmd << LIMITER | cmd1 >> file
*/