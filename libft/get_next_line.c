/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:31:09 by vlaggoun          #+#    #+#             */
/*   Updated: 2024/06/25 15:41:08 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean(char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * ft_strlen(buffer) - i + 1);
	if (!tmp)
		return (NULL);
	i++;
	while (buffer[i])
		tmp[j++] = buffer[i++];
	tmp[j] = '\0';
	free (buffer);
	return (tmp);
}

char	*read_line(int fd, char *buffer)
{
	int		i;
	char	*tmp;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	i = 1;
	while (i != 0)
	{	
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[i] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(tmp);
	return (buffer);
}

char	*set_line(char *buffer)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		tmp[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		tmp[i] = buffer[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	new_line = read_line(fd, new_line);
	if (!new_line)
		return (NULL);
	line = set_line(new_line);
	new_line = clean(new_line);
	return (line);
}
/*
#include<fcntl.h>

int    main(void)
{
    int            fd;
    char        *line;
    int            i;

    fd = open("a.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening the file");
        return (1);
    }
    i = 0;
    while (i < 8)
    {
        line = get_next_line(fd);
        printf("%s", line);
        free(line);
        i++;
    }
    close(fd);
    return (0);
}
*/
