/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:56 by evlim             #+#    #+#             */
/*   Updated: 2024/10/21 10:55:24 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	ft_count_words_pipe(char const *str, char delimiter)
// {
// 	int		i;
// 	int		count;
// 	char	d;

// 	i = 0;
// 	count = 0;
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] == delimiter)
// 		{
// 			i++;
// 		}
// 		if (str[i] == '\0')
// 		{
// 			break ;
// 		}
// 		count++;
// 		while (str[i] != '\0' && str[i] != delimiter)
// 		{
// 			if (ft_is_quotes(str[i]))
// 			{
// 				d = str[i++];
// 				while (str[i] != '\0' && str[i] != d)
// 				{
// 					i++;
// 				}
// 			}
// 			if (str[i] != '\0')
// 			{
// 				i++;
// 			}
// 		}
// 	}
// 	printf("count = %d\n", count);
// 	return (count);
// }

// int	ft_word_length_pipe(char const *s, char c)
// {
// 	int		i;
// 	int		word_length;
// 	char	quote;

// 	i = 0;
// 	word_length = 0;
// 	while (s[i] && s[i] != c)
// 	{
// 		if (ft_is_quotes(s[i]))
// 		{
// 			quote = s[i++];
// 			while (s[i] && s[i] != quote)
// 			{
// 				i++;
// 			}
// 			if (s[i])
// 			{
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			i++;
// 		}
// 		word_length++;
// 	}
// 	return (word_length);
// }

// void	*ft_free_alloc_pipe(char **new_string, int word)
// {
// 	int	i;

// 	i = 0;
// 	while (i < word)
// 	{
// 		free(new_string[i]);
// 		i++;
// 	}
// 	free(new_string);
// 	return (NULL);
// }

// char	**ft_copy_word_pipe(char const *s, char c, char **new_string)
// {
// 	int		i;
// 	int		j;
// 	int		word;
// 	int		length;
// 	char	quote;

// 	i = 0;
// 	word = 0;
// 	length = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 		{
// 			i++;
// 		}
// 		if (s[i] == '\0')
// 		{
// 			break ;
// 		}
// 		length = ft_word_length_pipe(&s[i], c);
// 		new_string[word] = malloc(length + 1);
// 		if (!new_string[word])
// 		{
// 			return (ft_free_alloc_pipe(new_string, word));
// 		}
// 		j = 0;
// 		while (s[i] && s[i] != c)
// 		{
// 			if (ft_is_quotes(s[i]))
// 			{
// 				quote = s[i++];
// 				while (s[i] && s[i] != quote)
// 				{
// 					new_string[word][j] = s[i];
// 					i++;
// 					j++;
// 				}
// 				if (s[i])
// 				{
// 					i++;
// 				}
// 			}
// 			else
// 			{
// 				new_string[word][j++] = s[i++];
// 			}
// 		}
// 		new_string[word][j] = '\0';
// 		word++;
// 	}
// 	return (new_string);
// }

// char	**ft_split_pipe(char const *s, char c)
// {
// 	int		counter_words;
// 	char	**new_string;

// 	if (!s)
// 	{
// 		return (NULL);
// 	}
// 	counter_words = ft_count_words_pipe(s, c);
// 	new_string = malloc((counter_words + 1) * sizeof(char *));
// 	if (!new_string)
// 	{
// 		return (NULL);
// 	}
// 	new_string[counter_words] = NULL;
// 	return (ft_copy_word_pipe(s, c, new_string));
// }


// int	ft_isspace(char c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n'
// 		|| c == '\v' || c == '\f' || c == '\r')
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_word_length_pipe(char const *s, char c)
// {
// 	int		i;
// 	int		word_length;
// 	char	quote;

// 	i = 0;
// 	word_length = 0;
// 	while (s[i] && ft_isspace(s[i]))
// 	{
// 		i++;
// 	}
// 	while (s[i] && s[i] != c)
// 	{
// 		if (ft_is_quotes(s[i]))
// 		{
// 			quote = s[i++];
// 			word_length++;
// 			while (s[i] && s[i] != quote)
// 			{
// 				word_length++;
// 				i++;
// 			}
// 		}
// 		word_length++;
// 		i++;
// 	}
// 	while (word_length > 0 && ft_isspace(s[i - 1]))
// 	{
// 		word_length--;
// 		i--;
// 	}
// 	printf("word length = %d\n", word_length);
// 	return (word_length);
// }
//
// void	*ft_free_alloc_pipe(char **new_string, int word)
// {
// 	int	i;

// 	i = 0;
// 	while (i < word)
// 	{
// 		free(new_string[i]);
// 		i++;
// 	}
// 	free(new_string);
// 	return (NULL);
// }

// char	**ft_copy_word_pipe(char const *s, char c, char **new_string, int i)
// {
// 	int	j;
// 	int	word;
// 	int	start;
// 	int	end;
//
// 	word = 0;
// 	while (word < ft_count_words_pipe(s, c))
// 	{
// 		while (s[i] != '\0' && (s[i] == c || ft_isspace(s[i])))
// 		{
// 			i++;
// 		}
// 		start = i;
// 		printf("start = %d\n", start);
// 		while (s[i] != '\0' && s[i] != c)
// 		{
// 			i++;
// 		}
// 		end = i - 1;
// 		printf("end = %d\n", end);
// 		while (end > start && isspace(s[end]))
// 		{
// 			end--;
// 		}
// 		new_string[word] = malloc((end - start + 2) * sizeof(char));
// 		if (!new_string[word])
// 		{
// 			return (ft_free_alloc_pipe(new_string, word));
// 		}
// 		j = 0;
// 		printf("start = %d | end = %d\n", start, end);
// 		while (start <= end)
// 		{
// 			new_string[word][j] = s[start];
// 			start++;
// 			j++;
// 		}
// 		new_string[word][j] = '\0';
// 		word++;
// 	}
// 	new_string[word] = NULL;
// 	return (new_string);
// }

// char	**ft_split_pipe(char const *s, char c)
// {
// 	int		counter_words;
// 	char	**new_string;
// 	int		i;

// 	i = 0;
// 	if (!s)
// 	{
// 		return (NULL);
// 	}
// 	counter_words = ft_count_words_pipe(s, c);
// 	new_string = malloc((counter_words + 1) * sizeof(char *));
// 	if (!new_string)
// 	{
// 		return (NULL);
// 	}
// 	new_string = ft_copy_word_pipe(s, c, new_string, i);
// 	return (new_string);
// }
