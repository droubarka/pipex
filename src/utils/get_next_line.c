/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:02:38 by mait-oub          #+#    #+#             */
/*   Updated: 2024/11/14 20:24:19 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*handle_eof(t_buffer *cache)
{
	char	*nextline;

	nextline = NULL;
	if (cache->size)
	{
		nextline = (char *) malloc(sizeof(char) * (cache->size + 1));
		if (nextline != NULL)
		{
			ft_memcpy((void *) nextline, cache->data, cache->size);
			nextline[cache->size] = 0;
		}
	}
	free(cache->data);
	cache->data = NULL;
	cache->size = 0;
	return (nextline);
}

static ssize_t	concate_line(char **nextline, size_t line_size, t_buffer *cache)
{
	t_buffer	nxtl;

	nxtl.size = cache->size + line_size + 1;
	nxtl.data = malloc(nxtl.size);
	if (nxtl.data != NULL)
	{
		ft_memcpy(nxtl.data, cache->data, cache->size);
		ft_memcpy(nxtl.data + cache->size, (void *) *nextline, line_size);
		((char *)(nxtl.data))[nxtl.size - 1] = 0;
		free(cache->data);
		cache->size = 0;
		free(*nextline);
		*nextline = (char *) nxtl.data;
		return ((ssize_t) nxtl.size - 1);
	}
	free(cache->data);
	cache->size = 0;
	free(*nextline);
	*nextline = NULL;
	return (-1);
}

static char	*_catln(char **nxtl, size_t size, t_buffer *cache, t_buffer *buffer)
{
	if (concate_line(nxtl, size, cache) != -1)
	{
		cache->data = buffer->data;
		cache->size = buffer->size;
		buffer->data = NULL;
	}
	return (*nxtl);
}

static char	*read_buffer(int fd, t_buffer *cache, t_buffer *buffer)
{
	char	*nextline;
	ssize_t	read_ssize;
	ssize_t	line_ssize;

	read_ssize = read(fd, buffer->data, BUFFER_SIZE);
	while (read_ssize)
	{
		if (read_ssize == -1)
			return (free(cache->data), cache->size = 0, NULL);
		buffer->size = (size_t) read_ssize;
		line_ssize = get_line(&nextline, buffer);
		if (line_ssize == -1)
		{
			free(cache->data);
			cache->size = 0;
			return (NULL);
		}
		if (line_ssize != 0)
			return (_catln(&nextline, (size_t) line_ssize, cache, buffer));
		if (join_buffer(cache, *buffer) == -1)
			return (NULL);
		read_ssize = read(fd, buffer->data, BUFFER_SIZE);
	}
	return (nextline = handle_eof(cache), nextline);
}

char	*get_next_line(int fd)
{
	static t_buffer	cache;
	t_buffer		buffer;
	char			*nextline;

	if (!BUFFER_SIZE || fd < 0)
		return (NULL);
	if (cache.size && get_line(&nextline, &cache))
		return (nextline);
	buffer.size = BUFFER_SIZE;
	buffer.data = malloc(buffer.size);
	if (buffer.data == NULL)
	{
		free(cache.data);
		cache.size = 0;
		return (NULL);
	}
	nextline = read_buffer(fd, &cache, &buffer);
	free(buffer.data);
	return (nextline);
}
