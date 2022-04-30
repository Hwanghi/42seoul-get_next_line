/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:29:34 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/30 18:29:04 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*make_newline(t_list *lst)
{
	char	*newline;
	char	*tmp;
	size_t	len;

	len = len_newline(lst->save);
	tmp = lst->save;
	newline = gnl_strldup(lst->save, len + 1);
	if (!newline)
		return (NULL);
	lst->len -= len;
	if (lst->len == 0)
		lst->save = NULL;
	else if (lst->len > 0)
	{
		lst->save = gnl_strldup(&(lst->save[len]), lst->len + 1);
		if (!lst->save)
		{
			free(tmp);
			free(newline);
			return (NULL);
		}
	}
	free(tmp);
	return (newline);
}

t_list	*find_or_new_fd(t_list **lst, int fd)
{
	t_list	*curr;

	if (*lst == NULL)
	{
		*lst = gnl_newlst(fd);
		return (*lst);
	}
	curr = *lst;
	while (curr->fd != fd)
	{
		if (curr->next == NULL)
		{
			curr->next = gnl_newlst(fd);
			return (curr->next);
		}
		curr = curr->next;
	}
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

ssize_t	read_file(int fd, t_list *lst)
{
	ssize_t	res;
	char	*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	while (1)
	{
		res = read(fd, buf, BUFFER_SIZE);
		if (res <= 0)
			break ;
		buf[res] = '\0';
		if (!save_buf(lst, buf, lst->len + res + 1))
		{
			res = -1;
			break ;
		}
		if (len_newline(lst->save) < lst->len)
			break ;
		if (lst->save[lst->len - 1] == '\n')
			break ;
	}
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst = NULL;
	t_list			*curr;
	ssize_t			res;

	if (fd < 0)
		return (NULL);
	curr = find_or_new_fd(&fd_lst, fd);
	if (!curr)
		return (NULL);
	res = read_file(fd, curr);
	if (res < 0 || (res == 0 && curr->save == NULL))
	{
		gnl_lstdelone(&fd_lst, fd);
		return (NULL);
	}
	return (make_newline(curr));
}
