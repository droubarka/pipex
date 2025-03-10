/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:14:20 by mait-oub          #+#    #+#             */
/*   Updated: 2024/11/14 20:24:42 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# if defined BUFFER_SIZE && BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buffer {
	void	*data;
	size_t	size;
}	t_buffer;

char	*get_next_line(int fd);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
ssize_t	ltrim_buffer(t_buffer *buffer, size_t n);
ssize_t	get_line(char **lineptr, t_buffer *buffer);
ssize_t	join_buffer(t_buffer *buf1, t_buffer buf2);

#endif
