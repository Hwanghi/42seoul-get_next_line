/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:27:10 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/30 18:07:16 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	len_newline(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

t_list	*gnl_newlst(int fd)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->fd = fd;
	lst->save = NULL;
	lst->len = 0;
	lst->next = NULL;
	return (lst);
}

void	gnl_lstdelone(t_list **lst, int fd)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *lst;
	while (curr != NULL)
	{
		if (curr->fd == fd)
		{
			if (prev == NULL)
				*lst = curr->next;
			else
				prev->next = curr->next;
			if (curr->save != NULL)
				free(curr->save);
			curr->next = NULL;
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

char	*gnl_strldup(char const *src, size_t dstsize)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(dstsize);
	if (!dst)
		return (NULL);
	i = 0;
	if (src != NULL)
	{
		while (src[i] != '\0' && i + 1 < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (dst);
}
