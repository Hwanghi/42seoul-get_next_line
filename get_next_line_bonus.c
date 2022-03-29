/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:39:47 by hehwang           #+#    #+#             */
/*   Updated: 2022/03/29 22:58:58 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MODIFY 1
#define NEWLINE 2

typedef struct s_list
{
	char			*str;
	int				fd;
	int				state;
	struct s_list	*next;
	struct s_list	*next_head;
}	t_list;

void free_all(t_list **head)
{
	if (head != NULL)
	{
		while (*head != NULL)
		{
			if ((*head)->str != NULL)
				free((*head)->str);
			tmp = (*head)->next;
			free(*head);
			*head = NULL;
			*head = tmp;
		}
	}
}

t_list	*gnl_newlst(char buf[], ssize_t len, int state)
{
	t_list	*node;
	ssize_t	i;

	node = (t_list *)malloc(sizeof(t_list) * 1);
	if (!node)
		return (NULL);
	node->str = (char *)malloc(sizeof(char) * (len + 1));
	if (!node->str)
	{
		free(node);
		return (NULL);
	}
	i = -1;
	while (++i < len)
		node->str[i] = buf[i];
	node->str[i] = '\0';
	node->next = NULL;
	return (node);
}

int	gnl_lstadd_back(t_list **head, t_list *new)
{
	t_list *tmp;

	if (!new)
	{
		free_all(head);
		return (0);
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	gnl_lstsplit_buf(t_list **head, char buf[], ssize_t read_bytes)
{
	ssize_t	i;
	ssize_t	len;

	i = 0;
	len = 0;
	while (i + len < read_bytes)
	{
		if (buf[i + len] == '\n')
		{
			if(!gnl_lstadd_back(head, gnl_newlst(&buf[i], ++len, NEWLINE)))
				return (0);
			i += len;
			len = 0;
		}
		else
			len++;
	}
	if (i < read_bytes)
	{
		new = gnl_newlst(&buf[i], len, MODIFY);
		if(!gnl_lstadd_back(head, gnl_newlst(buf[i], len, NEWLINE)))
			return (0);
	}
	return (1);
}

void	gnl_lstmodify(t_list **head)
{
	t_list *new_line;

	new_line = *head;
	while (new_line)
	{
		if (new_line->state == NEW_LINE)
			break ;
		new_line = new_line->next;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst;
	t_list			*head;
	char			buf[BUFFER_SIZE];
	ssize_t			read_bytes;

	// find fd
	head = find_fd(&fd_lst, fd);
	if (!head)
		head  = new_fd(&fd_lst, fd);
	while (1)
	{	
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		if(read_bytes == 0 && !head->next)
		{
			del_fd(&fd_lst, fd);
			return (NULL);
		}
		if (!gnl_lstsplit_buf(&head, buf, read_bytes))
			return (NULL);
		if (head->next->state == MODIFY)
			modify(head);
		if (head->next->state == NEWLINE)
		{
			// 노드 삭제 하고 free
			return (pop(head));
		}
	}
	// fd head 추가
	// lst pop 있으면 -> return
	// 없으면
	// read (pop 할 때 까지)
	// set_lst (split -> add lst back);
	// return ();
}
