/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:56 by evlim             #+#    #+#             */
/*   Updated: 2024/11/07 14:36:58 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_words_pipe(char const *str, char delimiter)
{
	int		i;
	int		count;
	char	d;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == delimiter)
			i++;
		while (str[i] != '\0' && str[i] != delimiter)
		{
			if (ft_is_quotes(str[i]))
			{
				d = str[i++];
				while (str[i] != '\0' && str[i] != d)
				{
					i++;
				}
			}
			i++;
		}
		count++;
	}
	printf("NB WORDS = %d\n", count);
	return (count);
}

int	ft_word_length_pipe(char const *s, char c)
{
	int		i;
	int		word_length;

	i = 0;
	word_length = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] != c)
		{
			if (s[i] == c)
			{
				word_length++;
				break ;
			}
			word_length++;
			i++;
		}
		i++;
		word_length++;
	}
	printf("s[i] = %c\n", s[i]);
	printf("LEN WORD = %d\n", word_length);
	return (word_length);
}

void	*ft_free_alloc_pipe(char **new_string, int word)
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

char	**ft_copy_word_pipe(char const *s, char c, char **new_string, int i)
{
	int		j;
	int		word;

	word = 0;
	while (word < ft_count_words_pipe(s, c))
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		new_string[word] = malloc(ft_word_length_pipe(&s[i], c) + 1);
		if (!new_string[word])
			return (ft_free_alloc(new_string, i));
		j = 0;
		while (s[i])
		{
			while (s[i] != '\0' && s[i] != c)
			{
					new_string[word][j] = s[i];
					printf("j = %c\n", new_string[word][j]);
					i++;
					j++;
			}
			printf("s[i] = %c\n", s[i]);
			printf("C = %c\n", c);
			if (s[i] == c)
			{
				new_string[word][j] = c;
				printf("j = %c\n", new_string[word][j]);
			}
			j++;
			i++;
		}
		new_string[word][j] = '\0';
		printf("N  WORD = %s\n", new_string[word]);
		word++;
	}
	return (new_string);
}

char    **ft_split_pipe(char const *s, char c)
{
	int		counter_words;
	char	**new_string;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	counter_words = ft_count_words_pipe(s, c);
	new_string = malloc((counter_words + 1) * sizeof(char *));
	if (!new_string)
		return (NULL);
	new_string[counter_words] = NULL;
	new_string = ft_copy_word_pipe(s, c, new_string, i);
	return (new_string);
}
