#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 100

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

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUFFER_SIZE];
	ssize_t		read_bytes;

	line = NULL;
	while (!is_newline(line))
	{
		if (!buf[0])	// buf is empty
		{
			read_bytes = read(fd, buf, BUFFER_SIZE);
			if (read_bytes < 0)
			{
				if (line != NULL)
					free(line);
				return (NULL);
			}
			else if (read_bytes == 0)
				return (line);
		}
		line = make_newline(line, buf);
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
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_putstr_fd(line, 1);
		free(line);
	}
	close(fd);
	return (0);
}
