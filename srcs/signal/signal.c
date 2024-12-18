/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:29:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/18 18:07:51 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_signal_global;

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	exit_code_sig(int signal)
{
	if (signal == SIGINT)
		g_signal_global = 130;
}

void	sigint_handler(int signal)
{
	//int	child;

	//child = 0;
	// if (signal == SIGQUIT)
		// printf("Quit (core dumped)\n");
	if (signal == SIGINT)
	{	
		g_signal_global = 130;
		close(STDIN_FILENO);
	}
	else
		return ;
}

void	set_signal(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
	//exit_code_sig(signal);
}

void	here_doc_sig_handler(int signal)
{
	(void)signal;
	g_signal_global = 130;
	close(STDIN_FILENO);
}
