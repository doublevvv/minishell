/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:29:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/12/16 10:18:15 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int g_signal_global;

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
		//mettre a jour la globale
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
	// sigaction(SIGQUIT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
	//exit_code_sig(signal);
}
// dans le here doc, fermer strdin(close[0]) et fermer la globale
//restaurer dans les forks signal(SIGQUIT/INT, SIG_DFL)
//debut exec/parent, signal(SIGINT, SIG_IGN)


void	here_doc_sig_handler()
{
	g_signal_global = 130;
	close(STDIN_FILENO);
}
