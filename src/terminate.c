/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:56 by mait-oub          #+#    #+#             */
/*   Updated: 2025/03/08 04:01:58 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	terminate(const char *s, int status)
{
	static char	argv_0[PATH_MAX];
	char		buffer[TERMINATE_BUFFER_SIZE];

	if (status == -2)
	{
		*argv_0 = 0;
		ft_strlcat(argv_0, s, PATH_MAX);
		return (-2);
	}
	if (s != NULL)
	{
		*buffer = 0;
		ft_strlcat(buffer, argv_0, TERMINATE_BUFFER_SIZE);
		ft_strlcat(buffer, ": ", TERMINATE_BUFFER_SIZE);
		ft_strlcat(buffer, s, TERMINATE_BUFFER_SIZE);
		perror(buffer);
	}
	if (-1 < status)
	{
		exit(status);
	}
	return (status);
}
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

void	close_stdio(int *stdio)
{
	if (stdio[0] != -1)
		close(stdio[0]);
	if (stdio[1] != -1)
		close(stdio[1]);

	stdio[0] = -1;
	stdio[1] = -1;
}
