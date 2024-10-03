/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:58:31 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/08/20 15:44:49 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*pourfree(char **phrase, int i)
{
	while (i >= 0)
		free(phrase[i--]);
	free(phrase);
	return (NULL);
}

static int	separateur(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int	nbrmots(const char *s, const char c)
{
	int	i;

	i = 0;
	while (s && *s && separateur(*s, c))
		s++;
	if (s && *s && !separateur(*s, c))
		i++;
	while (s && *s && !separateur(*s, c))
		s++;
	if (s && *s && separateur(*s, c))
		i += nbrmots(s, c);
	return (i);
}

static int	taillemot(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !separateur(s[i], c))
		i++;
	return (i);
}

char	**ft_split(const char *s, char c)
{
	int				i;
	int				j;
	int				mot;
	char			**tab;

	mot = nbrmots(s, c);
	tab = (char **)malloc(sizeof(char *) * (mot + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < mot)
	{
		while (separateur(*s, c))
			s++;
		tab[i] = malloc(sizeof(char) * (taillemot(s, c) + 1));
		if (!tab[i])
			return (pourfree(tab, i));
		j = 0;
		while (*s && !separateur(*s, c))
			tab[i][j++] = *s++;
		tab[i][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
/*
int		main(void)
{
	int i = 0;
	char **tab;

	tab = ft_split("tarte aux pommes choco", ' ');
	while (i < 4)
	{
		printf("string %d : %s\n", i, tab[i]);
		i++;
	}
	pourfree(tab, i);
	return (0);
}
*/
