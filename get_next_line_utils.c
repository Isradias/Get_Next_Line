/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas- <icaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:27:58 by icaldas-          #+#    #+#             */
/*   Updated: 2026/03/06 12:52:31 by icaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(int n)
{
	char	*ptr;
	int		i;

	ptr = malloc(n);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (i < n)
		ptr[i++] = '\0';
	return ((void *)ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char) c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	n;
	char	*ptr;

	n = 0;
	while (s[n])
		n++;
	ptr = ft_calloc(n + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[n] = '\0';
	while (n > 0)
	{
		n--;
		ptr[n] = s[n];
	}
	return (ptr);
}
