/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:27:10 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/07 22:02:49 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strlcat(t_list **curr, size_t cat_len)
{
	char	*dst;
	char	*src;
	size_t	i;

	src = (*curr)->line;
	dst = (char *)malloc((*curr)->len + cat_len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	if (src != NULL)
	{
		while (src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		//free(src);
	}
	while (i < (*curr)->len + cat_len)
	{
		dst[i] = (*curr)->buf[i - (*curr)->len];
		i++;
	}
	dst[i] = '\0';
	(*curr)->len += cat_len;
	return (dst);
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
	flush_buf(lst->buf, BUFFER_SIZE);
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

void	flush_buf(char buf[], size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return ;
	while (i + len < BUFFER_SIZE)
	{
		buf[i] = buf[len + i];
		i++;
	}
	while (i < BUFFER_SIZE)
		buf[i++] = 0;
}
