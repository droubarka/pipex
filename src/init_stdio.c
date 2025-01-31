/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stdio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 09:57:46 by mait-oub          #+#    #+#             */
/*   Updated: 2025/02/01 00:08:05 by mait-oub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_stdio_final(t_child *child, int *upstream, char *outfile)
{
	child->stdio[0] = *upstream;
	*upstream = -1;
	child->stdio[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (child->stdio[1] == -1)
		return (-1);
	return (0);
}

int	init_stdio(t_child *child, int n_childs, int *upstream, char **iofiles)
{
	int	pipefd[2];

	if (child->rank == 0)
	{
		*upstream = open(iofiles[0], O_RDONLY);
		if (*upstream == -1)
			terminate(iofiles[0], -1);
	}
	if (child->rank == n_childs - 1)
	{
		if (init_stdio_final(child, upstream, iofiles[1]) == -1)
			terminate(iofiles[1], -1);
		return (0);
	}
	if (pipe(pipefd) == -1)
	{
		terminate("pipe error", -1);
		return (-1);
	}
	child->stdio[0] = *upstream;
	child->stdio[1] = pipefd[1];
	*upstream = pipefd[0];
	return (0);
}
