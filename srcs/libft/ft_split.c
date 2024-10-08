/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:56 by evlim             #+#    #+#             */
/*   Updated: 2024/10/08 16:01:16 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    ft_count_words(char const *str, char delimiter)
{
    int    i;
    int    count;
    char    d;

    i = 0;
    count = 0;
    while (str[i] != '\0')
    {
        while (str[i] == delimiter)
            i++;
        // if (str[i] != '\0' && str[i] != delimiter)
        // {
        //     count++;
        // }
        while (str[i] != '\0' && str[i] != delimiter)
        {
            if (str[i] == '\'' || str[i] == '"')
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

int    ft_word_length(char const *s, char c)
{
    int    i;
    int    word_length;
    char    d;

    (void)d;
    i = 0;
    word_length = 0;
    while (s[i] == c)
	{
        i++;
	}
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
            i++;
            word_length += 2;
        }
        else
        {
            word_length++;
            i++;
        }
    }
	printf("LEN WORD = %d\n", word_length);
    return (word_length);
}

void	*ft_free_alloc(char **new_string, int word)
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

char	**ft_copy_word(char const *s, char c, char **new_string, int i)
{
	// printf("WORD LENGTH = %d\n", ft_word_length(&s[i], c));
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
			if (s[i] == '"')
			{
				// printf("JE SUIS DOUBLE QUOTE\n");
				new_string[word][j] = s[i];
				i++;
				j++;
				while (s[i] != '\0' && s[i] != '"')
				{
					new_string[word][j] = s[i];
					i++;
					j++;
				}
					new_string[word][j] = s[i];
					i++;
					j++;
			}
			else
			{
				new_string[word][j] = s[i];
				i++;
				j++;
			}
		}
		new_string[word][j] = '\0';
		printf("N  WORD = %s\n", new_string[word]);
		word++;
	}
	return (new_string);
}

char    **ft_split(char const *s, char c)
{
	int		counter_words;
	char	**new_string;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
    counter_words = ft_count_words(s, c);
	new_string = malloc((counter_words + 1) * sizeof(char *));
	if (!new_string)
		return (NULL);
    new_string[counter_words] = NULL;
    new_string = ft_copy_word(s, c, new_string, i);
	return (new_string);
}
