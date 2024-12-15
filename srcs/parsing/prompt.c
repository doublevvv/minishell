/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/13 16:32:50 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* The ft_execute_builtin() function calls the corresponding builtin command's 
function and updates the code status accordingly. */
void	ft_execute_builtin(t_main *msh, int i)
{
	if (i == ECHO)
	{
		dprintf(2, "APPEL ECHO FONCTION\n");
		msh->code_status = ft_echo(msh, msh->env);
	}
	else if (i == CD)
	{
		dprintf(2, "APPEL CD FONCTION\n");
		msh->code_status = ft_cd(msh, msh->env);
	}
	else if (i == PWD)
	{
		dprintf(2, "APPEL PWD FONCTION\n");
		msh->code_status = ft_pwd(msh, NULL);
	}
	else if (i == EXPORT)
	{
		dprintf(2, "APPEL EXPORT FONCTION\n");
		msh->code_status = ft_export(msh, msh->env);
	}
	else if (i == UNSET)
	{
		dprintf(2, "APPEL UNSET FONCTION\n");
		msh->code_status = ft_unset(msh, msh->env);
	}
	else if (i == ENV)
	{
		dprintf(2, "APPEL ENV FONCTION\n");
		ft_env(msh->env);
	}
	else if (i == EXIT)
	{
		dprintf(2, "APPEL EXIT FONCTION\n");
		msh->code_status = ft_exit(msh, NULL);
	}
}

/* The ft_is_builtin() function checks whether the given string matches one of 
the builtin commands and returns the corresponding index of the command in the 
builtin array. If the command is not found, it returns -1. */
int	ft_is_builtin(char *str)
{
	int			i;
	int			builtin_found;
	const char	*builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

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

/* The ft_identify_token() function allows us to identify specific tokens in
a string like pipes (|) and redirections (<, >, <<, >>). By updating the index,
we move past the token and continue checking the rest of the string.
The return value indicates the specific token identified or defaults to WORD
when no token is found, indicating that the current part of the string is a
regular word or an argument. */
int	ft_identify_token(char *str, int *index)
{
	int				i;
	int				token_found;
	const char		*token[] = {"|", "<", ">", "<<", ">>", NULL};

	i = 0;
	token_found = -1;
	while (token[i] != NULL)
	{
		if (ft_strncmp(token[i], str + *index, ft_strlen(token[i])) == 0)
		{
			token_found = i;
		}
		i++;
	}
	if (token_found != -1)
	{
		(*index) += ft_strlen(token[token_found]);
	}
	else
	{
		token_found = WORD;
	}
	return (token_found);
}

int	ft_get_word(t_main *msh, char *str, int *i)
{
	int	start;
	int	end;

	end = 0;
	ft_isspace(str, i);
	if (str[*i] == '\0')
	{
		return (EMPTY_LINE);
	}
	start = *i;
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '>' \
		&& str[*i] != '<' && str[*i] != '|')
	{
		if (ft_has_quote(str, i) == 0)
		{
			return (UNCLOSED_QUOTE);
		}
		(*i)++;
	}
	end = *i;
	msh->cmd = ft_substr(str, start, end - start);
	if (!msh->cmd)
	{
		return (ALLOCATION_FAILED);
	}
	if (start == end)
	{
		return (EMPTY_WORD);
	}
	return (SUCCESS);
}

bool	ft_check_prompt(t_main *msh, char *str)
{
	int		i;
	int		token;
	int		is_word;
	t_lst	*current_command;
	t_lst	*command;
	int		fd_infile;

	i = 0;
	token = 0;
	current_command = ft_lstnew(-1, NULL, -1);
	if (!current_command)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		return (false);
	}
	msh->head_command = current_command;
	command = NULL;
	if (str[i] == '\0')
	{
		return (false);
	}
	while (str[i])
	{
		token = ft_identify_token(str, &i);
		//dprintf(2, "token = %d\n", token);
		if (token == PIPE)
		{
			if (ft_verify_lst(msh->head_command) == false)
			{
				ft_print_error_message(EMPTY_WORD, '|');
				return (false);
			}
			//verifier que la current cmd est valide avant de creer la nouvelle cmd
			//dprintf(2, "FOUND PIPE\n");
			current_command = ft_lstnew(token, NULL, -1);
			if (!current_command)
			{
				ft_print_error_message(ALLOCATION_FAILED, 0);
				return (false);
			}
			ft_lstadd_back(msh, &msh->head_command, current_command);
		}
		else
		{
			is_word = ft_get_word(msh, str, &i);
			if (is_word != SUCCESS)
			{
				if (is_word != EMPTY_LINE)
				{
					ft_print_error_message(is_word, str[i]);
				}
				return (false);
			}
			//LEAK DANS HEREDOC
			if (token == REDIRECTION_HEREDOC)
			{
				signal(SIGINT, here_doc_sig_handler);
				dprintf(2, "WORD = REDIRECTION_HEREDOC\n");
				ft_generate_random_filename(msh);
				dprintf(2, "hd filename = %s\n", msh->heredoc_filename);
				msh->file = open(msh->heredoc_filename, O_CREAT | O_WRONLY, 0644);
				if (msh->file == -1)
				{
					dprintf(2, "HELLO HELLO\n");
					ft_open_file_error(msh, 0, 0);
					unlink(msh->heredoc_filename);
					free(msh->heredoc_filename);
					ft_free_all(msh, NULL, true);
				}
				dprintf(2, "msh->cmd = %s\n", msh->cmd);
				ft_read_input_heredoc(msh->cmd, msh->file);
				if (g_signal_global != 0)
				{
					if (dup2( msh->stdin_copy, STDIN_FILENO) == -1)
					{
						perror("signal heredoc echec dup2 stdin: ");
						ft_free_all(msh, NULL, true);
					}
					msh->code_status = g_signal_global;
					return (false);
				}
				close (msh->file);
				msh->file = -1;
				fd_infile = open(msh->heredoc_filename, O_RDONLY);
				dprintf(2, "msh->fd_infile: %d\n", fd_infile);
				if (fd_infile == -1)
				{
					ft_open_file_error(msh, 0, 0);
					unlink(msh->heredoc_filename);
					free(msh->heredoc_filename);
					ft_free_all(msh, NULL, true);
				}
				dprintf(2, "file: %d\n", msh->file);
				unlink(msh->heredoc_filename);
				free(msh->heredoc_filename);
				msh->heredoc_filename = NULL;
				dprintf(2, "fd_infile = %d\n", fd_infile);
				command = ft_lstnew(token, msh->cmd, fd_infile);
				signal(SIGINT, SIG_IGN);
			}
			else
			{
				command = ft_lstnew(token, msh->cmd, -1);
			}
			if (!command)
			{
				ft_print_error_message(ALLOCATION_FAILED, 0);
				return (false);
			}
			ft_lstadd_back(msh, &current_command->u_data.cmd_args, command);
		}
		ft_isspace(str, &i);
	}
	// Laisser la fonction (lst.c) en commentaire
	ft_display_lst(msh->head_command);
	if (ft_verify_lst(msh->head_command) == false)
	{
		ft_print_error_message(EMPTY_WORD, 0);
		return (false);
	}
	return (true);
}

void	ft_msh_loop(t_main *msh)
{
	while (1)
	{
		set_signal();
		msh->stdin_copy = dup(STDIN_FILENO);
		msh->stdout_copy = dup(STDOUT_FILENO);
		if (msh->stdin_copy == -1 || msh->stdout_copy == -1)
		{
			ft_putstr_fd("Failed to dup stdin/stdout\n", 2);
			ft_free_all(msh, NULL, true);
		}
		ft_init_data_bis(msh);
		msh->line = readline("les loutres > ");
		if (!msh->line)
		{
			//check erno == ENOMEN;
			ft_free_all(msh, NULL, false); //a verifier
			break ;
		}
		add_history(msh->line);
		if (ft_check_prompt(msh, msh->line) == false)
		{
			ft_free_all(msh, NULL, false);
			g_signal_global = 0;
		}
		else
		{
			ft_exec(msh);
		}
	}
	rl_clear_history();
}
