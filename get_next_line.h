/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:40:05 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/20 13:28:07 by hehwang          ###   ########.fr       */
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
char	*gnl_savebuf(t_list *lst, char *buf, size_t dstsize);
char	*make_newline(t_list *lst);
char	*gnl_strldup(char const *src, size_t dstsize);
ssize_t	read_file(int fd, t_list *lst);
t_list	*gnl_newlst(int fd);
t_list	*find_or_new_fd(t_list **lst, int fd);
void	gnl_lstdelone(t_list **lst, int fd);
char	*get_next_line(int fd);

#endif
