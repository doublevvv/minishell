/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:56 by evlim             #+#    #+#             */
/*   Updated: 2024/10/04 13:19:44 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_words(char const *str, char delimiter)
{
	int	i;
	int	count;
	int j;

	i = 0;
	count = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == delimiter)
			i++;
		if (str[i] != '\0' && str[i] != delimiter)
		{
			count++;
		}
		while (str[i] != '\0')
		{
			if (str[i] == '"')
			{
				printf("====== ICI ========\n");
				while (str[i] != '\0')
				{
					i++;
				}
				if (str[i - 1] == '"')
				{
					i++;
					count++;
				}
			}
			else if (str[i - 1] == delimiter && str[i] != delimiter)
			{
				count++;
				i++;
			}
			i++;
		}
	}
	printf("nb words = %d\n", count);
	return (count);
}

int	ft_word_length(char const *s, char c)
{
	int	i;
	int	word_length;

	i = 0;
	word_length = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '"')
			{
				word_length++;
				i++;
			}
		}
		else
		{
			i++;
			word_length++;
		}
	}
	printf("word length = %d\n", word_length);
	return (word_length);
}

static void	*ft_free_alloc(char **new_string, int word)
{
	int	i;

	i = 0;
	while (i < word)
	{
		free (new_string[word]);
		i++;
	}
	free (new_string);
	return (NULL);
}

static char	**ft_copy_word(char const *s, char c, char **new_string, int i)
{
	int	j;
	int	word;

	word = 0;
	while (word < ft_count_words(s, c))
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		new_string[word] = malloc(ft_word_length(&s[i], c) + 1);
		if (!new_string[word])
			return (ft_free_alloc(new_string, i));
		j = 0;
		while (s[i] != '\0' && s[i] != c)
		{
			new_string[word][j] = s[i];
			i++;
			j++;
		}
		new_string[word][j] = '\0';
		word++;
	}
	return (new_string);
}

char	**ft_split(t_main *msh, char const *s, char c)
{
	(void)*msh;
	int		counter_words;
	char	**new_string;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	counter_words = ft_count_words(s, c);
	printf("ND TOTAL DE MOTS = %d\n", counter_words);
	new_string = malloc((counter_words + 1) * sizeof(char *));
	if (!new_string)
		return (NULL);
	new_string[counter_words] = NULL;
	new_string = ft_copy_word(s, c, new_string, i);
	return (new_string);
}
