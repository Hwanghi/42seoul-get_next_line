/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:29:34 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/07 18:33:06 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	make_line(t_list **curr)
{
	size_t	cat_len;

	cat_len = find_line_end((*curr)->buf);
	(*curr)->len = gnl_strlcat(&((*curr)->line), (*curr)->buf, cat_len);
	flash_buf((*curr)->buf, cat_len);
	return ((*curr)->len);
}

t_list	*find_or_new_fd(t_list **fd_lst, int fd)
{
	t_list *new;
	t_list *curr;

	new = gnl_newlst(fd);
	if (!new)
		return (NULL);
	if (*fd_lst == NULL)
	{
		*fd_lst = new;
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
	curr->next = new;
	return (new);
}

char	*pop_fd(t_list **fd_lst, int fd, int read_bytes)
{
	char	*line;
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
			line = curr->line;
			free(curr);
			if (read_bytes < 0)
			{
				if (line != NULL)
					free(line);
				return (NULL);
			}
			return (line);
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
		make_line(&curr);
	}
	return (curr->line);
}
