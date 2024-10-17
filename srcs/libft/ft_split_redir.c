/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:28:07 by evlim             #+#    #+#             */
/*   Updated: 2024/10/17 16:17:59 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	is_redirection(char c)
// {
//     return (c == '>' || c == '<');
// }

// int	is_double_redirection(const char *str)
// {
//     return ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'));
// }

// int	ft_count_words_redir(char const *str, char delimiter)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;

// 	while (str[i] != '\0')
// 	{
// 		while (str[i] == delimiter)
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		if (is_double_redirection(&str[i]))
// 		{
// 			count++;
// 			i += 2;
// 		}
// 		else if (is_redirection(str[i]))
// 		{
// 			count++;
// 			i++;
// 		}
// 		else
// 		{
// 			count++;
// 			while (str[i] != '\0' && str[i] != delimiter && !is_redirection(str[i]))
// 				i++;
// 		}
// 	}
// 	return (count);
// }

// int	ft_word_length_redir(char const *s, char delimiter)
// {
// 	int	i;

// 	i = 0;
// 	if (is_double_redirection(s))
// 	{
// 		return (2);
// 	}
// 	if (is_redirection(s[0]))
// 	{
// 		return (1);
// 	}
// 	while (s[i] != '\0' && s[i] != delimiter && !is_redirection(s[i]))
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// void	*ft_free_alloc_redir(char **new_string, int word)
// {
// 	int	i;

// 	i = 0;
// 	while (i < word)
// 	{
// 		free(new_string[word]);
// 		i++;
// 	}
// 	free(new_string);
// 	return (NULL);
// }

// char	**ft_copy_word_redir(char const *s, char delimiter, char **new_string, int i)
// {
// 	int	j;
// 	int	word;
// 	int	length;

// 	j = 0;
// 	word = 0;
// 	length = 0;
// 	while (word < ft_count_words_redir(s, delimiter))
// 	{
// 		while (s[i] == delimiter)
// 			i++;
// 		length = ft_word_length_redir(&s[i], delimiter);
// 		new_string[word] = malloc((length + 1) * sizeof(char));
// 		if (!new_string[word])
// 			return (ft_free_alloc_redir(new_string, word));
// 		j = 0;
// 		if (is_double_redirection(&s[i]))
// 		{
// 			new_string[word][j++] = s[i++];
// 			new_string[word][j++] = s[i++];
// 		}
// 		else if (is_redirection(s[i]))
// 		{
// 			new_string[word][j++] = s[i++];
// 		}
// 		else
// 		{
// 			while (s[i] != '\0' && s[i] != delimiter && !is_redirection(s[i]))
// 			{
// 				new_string[word][j++] = s[i++];
// 			}
// 		}
// 		new_string[word][j] = '\0';
// 		word++;
// 	}
// 	return (new_string);
// }

// char	**ft_split_redir(char const *s, char delimiter)
// {
// 	int		counter_words;
// 	char	**new_string;

// 	if (!s)
// 		return (NULL);
// 	counter_words = ft_count_words_redir(s, delimiter);
	// printf("counter_words = %d\n", counter_words);
// 	new_string = malloc((counter_words + 1) * sizeof(char *));
// 	if (!new_string)
// 		return (NULL);
// 	new_string[counter_words] = NULL;
// 	new_string = ft_copy_word_redir(s, delimiter, new_string, 0);
// 	return (new_string);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evlim <evlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:56 by evlim             #+#    #+#             */
/*   Updated: 2024/10/10 14:27:57 by evlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_words_redir(char const *str, char delimiter)
{
	int		i;
	int		count;
	char	d;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == delimiter)
		{
			count++;
			i++;
			while (str[i] == delimiter)
				i++;
		}
		count++;
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
			if (str[i] != '\0')
			{
				i++;
			}
		}
	}
	printf("count = %d\n", count);
	return (count);
}

int	ft_word_length_redir(char const *s, char c)
{
	int		i;
	int		word_length;
	char	d;

	i = 0;
	word_length = 0;

	printf("NOEUD 3: %s\n", s);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			word_length++;
			i++;
			while (s[i] == c)
				i++;
		}
		word_length++;
		while (s[i] != '\0' && s[i] != c)
		{
			if (ft_is_quotes(s[i]))
			{
				d = s[i++];
				while (s[i] != '\0' && s[i] != d)
				{
					i++;
				}
			}
			if (s[i] != '\0')
			{
				i++;
			}
		}
	}
	printf("LEN WORD = %d\n", word_length);
	return (word_length);
}

void	*ft_free_alloc_redir(char **new_string, int word)
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

char	**ft_copy_word_redir(char const *s, char c, char **new_string, int i)
{
	int		j;
	int		word;

	word = 0;
	while (word < ft_count_words_redir(s, c))
	{
		printf("NOEUD 4 : %s\n", s);
		new_string[word] = malloc(ft_word_length_redir(&s[i], c) + 1);
		if (!new_string[word])
			return (ft_free_alloc_redir(new_string, i));
		j = 0;
		while (s[i])
		{
			if (s[i] == c)
			{
				new_string[word][j] = s[i];
				i++;
				j++;
				printf("new string = %s\n", new_string[word]);
				break ;
			}
			new_string[word][j] = s[i];
			i++;
			j++;
		}
		new_string[word][j] = '\0';
		word++;
	}
	return (new_string);
}

char    **ft_split_redir(char const *s, char c)
{
	// printf("NOEUD : %s\n", s);
	int		counter_words;
	char	**new_string;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	counter_words = ft_count_words_redir(s, c);
	printf("counter words = %d\n", counter_words);
	new_string = malloc((counter_words + 1) * sizeof(char *));
	if (!new_string)
		return (NULL);
	new_string[counter_words] = NULL;
	// printf("NOEUD DE VERIT AVNT LENGHT : %s\n", s);
	new_string = ft_copy_word_redir(s, c, new_string, i);
	while (new_string[i])
	{
		printf("New string %s\n", new_string[i]);
		i++;	
	}	return (new_string);
}

