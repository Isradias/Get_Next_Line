/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas- <icaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:27:58 by icaldas-          #+#    #+#             */
/*   Updated: 2026/03/06 12:56:20 by icaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char *s1, char const *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len] != '\0')
		s1_len++;
	while (s2[s2_len] != '\0')
		s2_len++;
	ptr = ft_calloc(s1_len + s2_len + 1);
	if (ptr == NULL)
		return (NULL);
	while (s2_len - 1 >= 0)
	{
		ptr[s1_len + s2_len - 1] = s2[s2_len - 1];
		s2_len--;
	}
	while (s1_len - 1 >= 0)
	{
		ptr[s1_len - 1] = s1[s1_len - 1];
		s1_len--;
	}
	free(s1);
	return (ptr);
}

static char	*ft_readed(char **stash, int i)
{
	char	*line;
	char	*temp;

	line = ft_calloc(i + 2);
	i = 0;
	while (stash[0][i] != '\0' && stash[0][i] != '\n')
	{
		line[i] = stash[0][i];
		i++;
	}
	if (stash[0][i] == '\n')
		line[i++] = '\n';
	if (line[0] == '\0')
	{
		free(*stash);
		free(line);
		*stash = NULL;
		return (NULL);
	}
	temp = ft_strdup(*stash + i);
	free(*stash);
	*stash = temp;
	return (line);
}

static char	*ft_read_join(char **stash, int fd)
{
	ssize_t	bytes_read;
	int		i;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	i = 0;
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*stash = ft_strjoin(*stash, buffer);
		i = 0;
		while (stash[0][i] != '\n' && stash[0][i] != '\0')
			i++;
		if (stash[0][i] == '\n')
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (ft_readed(stash, i));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			i;

	i = 0;
	if (stash == NULL)
		stash = ft_calloc(1);
	if (!stash || fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		return (NULL);
	}
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		return (ft_readed(&stash, i));
	return (ft_read_join(&stash, fd));
}

#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("texto.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	printf("%s", get_next_line(fd));
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*line;

	while ((line = get_next_line(0)))
	{
		printf("%s", line);
		free(line);
	}
}*/
