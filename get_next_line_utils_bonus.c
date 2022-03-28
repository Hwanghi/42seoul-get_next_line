/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:39:18 by hehwang           #+#    #+#             */
/*   Updated: 2022/03/27 21:39:20 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	is_newline(char *line)
{
	if (!line)
		return (0);
	while (*line != '\0')
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*gnl_strndup(const char *s1, size_t n)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(sizeof(char) * (n));
	if (!dst)
		return (NULL);
	i = 0;
	while (i + 1 < n)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	dstsize;
	size_t	i;

	dstsize = gnl_strlen(s1) + gnl_strlen(s2) + 1;
	dst = (char *)malloc(sizeof(char) * (dstsize));
	if (!dst)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		while (*s1 != '\0')
			dst[i++] = *s1++;
	if (s2 != NULL)
		while (*s2 != '\0')
			dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}

size_t	find_end(char buf[])
{
	size_t i;

	i = 0;
	while (buf[i] && i < BUFFER_SIZE)
	{
		if (buf[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}
