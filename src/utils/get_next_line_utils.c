/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:52:16 by mait-oub          #+#    #+#             */
/*   Updated: 2024/11/14 20:24:34 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*x;

	x = (unsigned char *) s;
	while (n--)
	{
		if (*x == c)
		{
			return ((void *) x);
		}
		x++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*xdst;
	const unsigned char	*xsrc;

	xdst = (unsigned char *) dest;
	xsrc = (const unsigned char *) src;
	while (n--)
	{
		*xdst++ = *xsrc++;
	}
	return (dest);
}

ssize_t	ltrim_buffer(t_buffer *buffer, size_t n)
{
	t_buffer	new_buffer;

	new_buffer.size = buffer->size - n;
	if (new_buffer.size == 0)
	{
		buffer->size = new_buffer.size;
		free(buffer->data);
		buffer->data = NULL;
		return ((ssize_t) buffer->size);
	}
	new_buffer.data = malloc(new_buffer.size);
	if (new_buffer.data != NULL)
	{
		ft_memcpy(new_buffer.data, buffer->data + n, new_buffer.size);
		free(buffer->data);
		buffer->data = new_buffer.data;
		buffer->size = new_buffer.size;
		return ((ssize_t) buffer->size);
	}
	return (-1);
}

ssize_t	get_line(char **lineptr, t_buffer *buffer)
{
	void	*nlptr;
	size_t	length;

	nlptr = ft_memchr(buffer->data, '\n', buffer->size);
	if (nlptr != NULL)
	{
		length = (nlptr - buffer->data) + 1;
		*lineptr = (char *) malloc(sizeof(char) * (length + 1));
		if (*lineptr != NULL)
		{
			ft_memcpy(*lineptr, buffer->data, length);
			(*lineptr)[length] = 0;
			if (ltrim_buffer(buffer, length) != -1)
				return ((ssize_t) length);
			free(*lineptr);
			*lineptr = NULL;
		}
		free(buffer->data);
		buffer->data = NULL;
		buffer->size = 0;
		return (-1);
	}
	return (0);
}

ssize_t	join_buffer(t_buffer *buf1, t_buffer buf2)
{
	t_buffer	new_buffer;

	new_buffer.size = buf1->size + buf2.size;
	new_buffer.data = malloc(new_buffer.size);
	if (new_buffer.data != NULL)
	{
		ft_memcpy(new_buffer.data, buf1->data, buf1->size);
		ft_memcpy(new_buffer.data + buf1->size, buf2.data, buf2.size);
		free(buf1->data);
		buf1->data = new_buffer.data;
		buf1->size = new_buffer.size;
		return ((ssize_t) buf1->size);
	}
	free(buf1->data);
	buf1->data = NULL;
	buf1->size = 0;
	return (-1);
}
