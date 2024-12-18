/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:47:54 by evlim             #+#    #+#             */
/*   Updated: 2024/12/18 18:05:56 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

bool	ft_isword(char *str, int is_word, int i)
{
	if (is_word != SUCCESS)
	{
		if (is_word != EMPTY_LINE)
			ft_print_error_message(is_word, str[i]);
		return (false);
	}
	return (true);
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
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\t' \
		&& str[*i] != '>' && str[*i] != '<' && str[*i] != '|')
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

bool	ft_check_str(t_main *msh, t_lst *current_command, char *str, int i)
{
	int		token;
	t_lst	*command;

	command = NULL;
	token = 0;
	while (str[i])
	{
		token = ft_identify_token(str, &i);
		if (token == PIPE)
		{
			current_command = ft_pipe_case(msh, token);
			if (!current_command)
				return (ft_display_error(msh));
		}
		else
		{
			if (ft_isword(str, ft_get_word(msh, str, &i), i) == false)
				return (false);
			command = ft_command(msh, token);
			ft_lstadd_back(msh, &current_command->u_data.cmd_args, command);
		}
		ft_isspace(str, &i);
	}
	return (true);
}

bool	ft_check_prompt(t_main *msh, char *str)
{
	int		i;
	t_lst	*current_command;
	t_lst	*command;

	i = 0;
	current_command = ft_lstnew(-1, NULL, -1);
	if (!current_command)
	{
		ft_print_error_message(ALLOCATION_FAILED, 0);
		return (false);
	}
	msh->head_command = current_command;
	command = NULL;
	if (str[i] == '\0')
		return (false);
	if (ft_check_str(msh, current_command, str, i) == false)
	{
		return (false);
	}
	ft_display_lst(msh->head_command); //A SUPPRIMER
	if (ft_verify_lst(msh->head_command) == false)
	{
		ft_print_error_message(EMPTY_WORD, 0);
		return (false);
	}
	return (true);
}
