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
	close(stdio[0]);
	close(stdio[1]);
}

void	free_array(char **array)
{
	while (*array)
	{
		free(array);
		array++;
	}
}

void	terminate(char *s, int status)
{
	static char	argv_0[PATH_MAX];
	char		buff[PATH_MAX + 128];

	if (status == -2)
	{
		argv_0 = s;
		return ;
	}
	if (s != NULL)
	{
		ft_strlcat(buff, argv_0);
		ft_strlcat(buff, ": ");
		ft_strlcat(buff, s);
		perror(buff);
	}
	if (status != -1)
		exit(status);
}
