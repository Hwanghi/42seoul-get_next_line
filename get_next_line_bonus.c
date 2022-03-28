/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:39:47 by hehwang           #+#    #+#             */
/*   Updated: 2022/03/28 12:32:37 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	flash_buf(char buf[], size_t end)
{
	size_t	i;

	i = 0;
	while (i + end < BUFFER_SIZE)
	{
		buf[i] = buf[end + i];
		i++;
	}
	while (i < BUFFER_SIZE)
		buf[i++] = 0;
}

void free_all(char *origin, char *add)
{
	if (origin != NULL)
		free(origin);
	if (add != NULL)
		free(add);
}

char *make_newline(char *origin, char buf[])
{
	char	*new_line;
	char	*add;
	size_t	end_i;

	end_i = find_end(buf);
	add = gnl_strndup(buf, end_i + 1);
	if (!add)
		return (NULL);
	flash_buf(buf, end_i);
	new_line = gnl_strjoin(origin, add);
	free_all(origin, add);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*new_buf()
{
	char	*buf;
	size_t	i;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
		buf[i++] = 0;
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf[OPEN_MAX];
	ssize_t		read_bytes;

	if (fd < 0)
		return (NULL);
	if (!buf[fd])
	{
		buf[fd] = new_buf();
		if (!buf[fd])
			return (NULL);
	}
	line = NULL;
	while (!is_newline(line))
	{
		if (!buf[fd][0])	// buf is empty
		{
			read_bytes = read(fd, buf[fd], BUFFER_SIZE);
			if (read_bytes < 0)
			{
				if (line != NULL)
					free(line);
				if (buf[fd] != NULL)
					free(buf[fd]);
				return (NULL);
			}
			else if (read_bytes == 0)
			{
				if (buf[fd] != NULL)
					free(buf[fd]);
				return (line);
			}
		}
		line = make_newline(line, buf[fd]);
		if (!line)
			return (NULL);
	}
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s != '\0')
		write(fd, s++, 1);
}

int	main(int ac, char **av)
{
	int		temp;
	int		fd[10];
	char	*line;
	int		i;

	i = 1;
	fd[0] = 0;
	while (i < ac)
	{
		fd[i] = open(av[i], O_RDONLY);
		i++;
	}
	i = 1;
	while ((line = get_next_line(fd[i%(ac)])) != NULL)
	{
		ft_putstr_fd(line, 1);
		free(line);
		i++;
	}
	i = 1;
	while (i < ac)
		close(fd[i++]);
	return (0);
}
