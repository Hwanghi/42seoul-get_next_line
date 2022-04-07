/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:29:34 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/07 22:29:32 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_or_new_fd(t_list **fd_lst, int fd)
{
	t_list *curr;

	if (*fd_lst == NULL)
	{
		*fd_lst = gnl_newlst(fd);
		return (*fd_lst);
	}
	curr = *fd_lst;
	while (curr->next != NULL)
	{
		if (curr->fd == fd)
		{
			curr->line = NULL;
			curr->len = 0;
			return (curr);
		}
		curr = curr->next;
	}
	curr->next = gnl_newlst(fd);
	return (curr->next);
}

char	*pop_fd(t_list **fd_lst, int fd, int read_bytes)
{
	char	*tmp;
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *fd_lst;
	while (curr != NULL)
	{
		if (curr->fd == fd)
		{
			if (prev == NULL)
				*fd_lst = curr->next;
			else
				prev->next = curr->next;
			tmp = curr->line;
			//free(curr);
			if (read_bytes < 0)
			{
				if (tmp != NULL)
					//free(tmp);
					read_bytes = 0;
				return (NULL);
			}
			return (tmp);
		}
		prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst = NULL;
	t_list			*curr;
	ssize_t			read_bytes;
	size_t			cat_len;

	if (fd < 0)
		return (NULL);
	curr = find_or_new_fd(&fd_lst, fd);
	if (!curr)
		return (NULL);
	while (!is_newline(curr->line, curr->len))
	{
		if (!curr->buf[0])	// buf is empty
		{
			read_bytes = read(curr->fd, curr->buf, BUFFER_SIZE);
			if (read_bytes <= 0)
				return (pop_fd(&fd_lst, curr->fd, read_bytes));
		}
		cat_len = find_line_end(curr->buf);
		curr->line = gnl_strlcat(&curr, cat_len);
		if (!curr->line)
			return (pop_fd(&fd_lst, curr->fd, -1));
		flush_buf(curr->buf, cat_len);
	}
	return (curr->line);
}
