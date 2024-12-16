/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:24:01 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/16 18:58:49 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* The ft_execute_builtin() function calls the corresponding builtin command's 
function and updates the code status accordingly. */
void	ft_execute_builtin(t_main *msh, int i)
{
	if (i == ECHO)
	{
		msh->code_status = ft_echo(msh, msh->env);
	}
	else if (i == CD)
	{
		msh->code_status = ft_cd(msh, msh->env);
	}
	else if (i == PWD)
	{
		msh->code_status = ft_pwd(msh, NULL);
	}
	else if (i == EXPORT)
	{
		msh->code_status = ft_export(msh, msh->env);
	}
	else if (i == UNSET)
	{
		msh->code_status = ft_unset(msh, msh->env);
	}
	else if (i == ENV)
	{
		ft_env(msh->env);
	}
	else if (i == EXIT)
	{
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
		return (EMPTY_LINE);
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
		return (ALLOCATION_FAILED);
	if (start == end)
		return (EMPTY_WORD);
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
		if (token == PIPE)
		{
			if (ft_verify_lst(msh->head_command) == false)
			{
				ft_print_error_message(EMPTY_WORD, '|');
				return (false);
			}
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
			if (token == REDIRECTION_HEREDOC)
			{
				signal(SIGINT, here_doc_sig_handler);
				ft_generate_random_filename(msh);
				msh->file = open(msh->heredoc_filename, O_CREAT | O_WRONLY, 0644);
				if (msh->file == -1)
				{
					ft_open_file_error(msh, 0, 0);
				}
				ft_read_input_heredoc(msh->cmd, msh->file);
				if (g_signal_global != 0)
				{
					if (dup2( msh->stdin_copy, STDIN_FILENO) == -1)
					{
						ft_free_all(msh, "Signal heredoc failed to dup2 stdin\n", true);
					}
					msh->code_status = 130;
					write(1, "\n", 1);
					return (false);
				}
				close (msh->file);
				msh->file = -1;
				fd_infile = open(msh->heredoc_filename, O_RDONLY);
				if (fd_infile == -1)
				{
					ft_open_file_error(msh, 0, 0);
				}
				unlink(msh->heredoc_filename);
				free(msh->heredoc_filename);
				msh->heredoc_filename = NULL;
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
	if (ft_verify_lst(msh->head_command) == false)
	{
		ft_print_error_message(EMPTY_WORD, 0);
		return (false);
	}
	return (true);
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

void	ft_copy_stdin_stdout(t_main *msh)
{
	msh->stdin_copy = dup(STDIN_FILENO);
	msh->stdout_copy = dup(STDOUT_FILENO);
	if (msh->stdin_copy == -1 || msh->stdout_copy == -1)
	{
		ft_putstr_fd("Failed to dup stdin/stdout\n", 2);
		ft_free_all(msh, NULL, true);
	}
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
		{
			ft_exec(msh);
		}
	}
	rl_clear_history();
}
