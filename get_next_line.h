/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:40:05 by hehwang           #+#    #+#             */
/*   Updated: 2022/05/17 15:37:05 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list {
	int				fd;
	char			*save;
	size_t			len;
	struct s_list	*next;
}	t_list;

size_t	len_newline(char const *s);
char	*gnl_strldup(char const *src, size_t dstsize);
t_list	*gnl_newlst(int fd);
void	gnl_lstdelone(t_list **lst, int fd);
char	*get_next_line(int fd);

#endif
