/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:40:05 by hehwang           #+#    #+#             */
/*   Updated: 2022/04/07 15:39:24 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list {
	char	buf[BUFFER_SIZE];
	int		fd;
	char	*line;
	size_t	len;
	struct s_list	*next;
}	t_list;

size_t	gnl_strlcat(char **str, char buf[], size_t cat_len);
t_list	*gnl_newlst(int fd);
int		is_newline(char *str, size_t len);
size_t	find_line_end(char buf[]);
void	flash_buf(char buf[], size_t end);
size_t	make_line(t_list **curr);
t_list	*find_or_new_fd(t_list **fd_lst, int fd);
char	*pop_fd(t_list **fd_lst, int fd, int read_bytes);
char	*get_next_line(int fd);

#endif
