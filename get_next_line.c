/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:29:34 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/19 19:53:08 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*make_newline(t_list *lst)
{
	char	*newline;
	char	*tmp;
	size_t	len;

	len = len_newline(lst->save);
	if (len == 0)
		return (NULL);
	newline = gnl_strldup(lst->save, len + 1);
	if (!newline)
		return (NULL);
	lst->len -= len;
	tmp = lst->save;
	if (lst->len > 0)
	{
		lst->save = gnl_strldup(&(lst->save[len]), lst->len + 1);
		if (!lst->save)
		{
			free(tmp);
			free(newline);
			return (NULL);
		}
	}
	else
		lst->save = NULL;
	free(tmp);
	return (newline);
}

t_list	*find_or_new_fd(t_list **lst, int fd)
{
	t_list *curr;

	if (*lst == NULL)
	{
		*lst = gnl_newlst(fd);
		return (*lst);
	}
	curr = *lst;
	while (curr != NULL)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	curr = gnl_newlst(fd);
	return (curr);
}

void	*save_buf(t_list *lst, char *buf, size_t dstsize)
{
	char	*dst;
	size_t	i;

	if (!lst)
		return (NULL);
	dst = (char *)malloc(dstsize);
	if (!dst)
		return (NULL);
	i = 0;
	if (lst->save != NULL)
	{
		while (lst->save[i] != '\0')
		{
			dst[i] = lst->save[i];
			i++;
		}
		free(lst->save);
	}
	while (*buf != '\0')
		dst[i++] = *buf++;
	dst[i] = '\0';
	lst->save = dst;
	lst->len = i;
	return (dst);
}

ssize_t	read_file(int fd, char *buf, t_list *lst)
{
	ssize_t	res;

	res = 0;
	while (len_newline(lst->save) >= lst->len)
	{
		res = read(fd, buf, BUFFER_SIZE);
		if (res <= 0)
			return (res);
		buf[res] = '\0';
		if (!save_buf(lst, buf, lst->len + res + 1))
			return (-1);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst = NULL;
	t_list			*curr;
	char			*buf;
	ssize_t			res;

	if (fd < 0)
		return (NULL);
	curr = find_or_new_fd(&fd_lst, fd);
	if (!curr)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	res = read_file(fd, buf, curr);
	free(buf);
	if (res < 0)
	{
		gnl_lstdelone(&curr, fd);
		return (NULL);
	}
	if (res == 0)
		if (!curr->save)
		{
			gnl_lstdelone(&curr, fd);
			return (NULL);
		}
	return (make_newline(curr));
}
