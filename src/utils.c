/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:56 by mait-oub          #+#    #+#             */
/*   Updated: 2025/01/31 00:00:57 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	xsleep(unsigned int seconds)
{
	int	counter;

	while (seconds--)
	{
		counter = 0;
		while (counter != -1)
			counter++;
	}
}

char	*pathjoin(char *path, char *filename)
{
	char	*pathname;
	char	*temp;

	pathname = ft_strjoin(path, "/");
	if (pathname != NULL)
	{
		temp = pathname;
		pathname = ft_strjoin(pathname, filename);
		free(temp);
	}
	return (pathname);
}

void	close_stdio(int *stdio)
{
	if (stdio[0] != -1)
		close(stdio[0]);
	if (stdio[1] != -1)
		close(stdio[1]);

	stdio[0] = -1;
	stdio[1] = -1;
}

void	free_array(char **array)
{
	char	**root;

	root = array;
	while (*array)
	{
		free(*array);
		array++;
	}
	free(root);
}

int	terminate(char *s, int status)
{
	static char	argv_0[PATH_MAX];
	char		buff[PATH_MAX + 128];

	if (status == -2)
	{
		ft_strlcpy(argv_0, s, PATH_MAX);
		return (-2);
	}
	if (s != NULL)
	{
		buff[0] = '\0';
		ft_strlcat(buff, argv_0, PATH_MAX + 128);
		ft_strlcat(buff, ": ", PATH_MAX + 128);
		ft_strlcat(buff, s, PATH_MAX + 128);
		perror(buff);
	}
	if (-1 < status)
		exit(status);
	return (status);
}
