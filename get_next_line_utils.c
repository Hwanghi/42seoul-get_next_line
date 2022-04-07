/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:27:10 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/07 18:25:51 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlcat(char **str, char buf[], size_t cat_len)
{
	char	*dst;
	char	*src;
	size_t	src_len;
	size_t	i;

	src = *str;
	src_len = 0;
	if (src != NULL)
		while (src[src_len] != '\0')
			src_len++;
	dst = (char *)malloc(src_len + cat_len + 1);
	if (!dst)
	{
		free(src);
		*str = NULL;
		return (0);
	}
	i = 0;
	if (src != NULL)
	{
		while (src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		free(src);
	}
	while (i < src_len + cat_len)
	{
		dst[i] = buf[i - src_len];
		i++;
	}
	dst[i] = '\0';
	*str = dst;
	return (src_len + cat_len);
}

t_list	*gnl_newlst(int fd)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->fd = fd;
	lst->line = NULL;
	lst->len = 0;
	flash_buf(lst->buf, BUFFER_SIZE);
	lst->next = NULL;
	return (lst);
}

int	is_newline(char *str, size_t len)
{
	size_t i;

	if (!str || len == 0)
		return (0);
	i = len - 1;
	if (str[i] == '\n')
		return (1);
	return (0);
}

size_t	find_line_end(char buf[])
{
	size_t i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buf[i] == '\n')
			return (i + 1);
		else if (buf[i] == '\0')
			return (i);
		i++;
	}
	return (BUFFER_SIZE);
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
