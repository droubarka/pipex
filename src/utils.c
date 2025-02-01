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
