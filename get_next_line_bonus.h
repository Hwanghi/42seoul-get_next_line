/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehwang <hehwang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:40:05 by hehwang           #+#    #+#             */
/*   Updated: 2022/03/27 21:32:24 by hehwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int	is_newline(char *line);
size_t	gnl_strlen(const char *s);
char	*gnl_strndup(const char *s1, size_t n);
char	*gnl_strjoin(char const *s1, char const *s2);
size_t	find_end(char buf[]);
void	flash_buf(char buf[], size_t end);
void free_all(char *origin, char *add);
char *make_newline(char *origin, char buf[]);
char	*get_next_line(int fd);

#endif
